#include "pch.h"
#include "Triangle.h"


Triangle::Triangle()
{
}

Triangle::Triangle(vec3 _v0, vec3 _v1, vec3 _v2, vec3 _normal0, vec3 _normal1, vec3 _normal2)
{
	this->_v0 = _v0;
	this->_v1 = _v1;
	this->_v2 = _v2;	
	this->_normal = normalize(cross((this->_v1 - this->_v0), (this->_v2 - this->_v0)));
	this->_normal0 = _normal0;
	this->_normal1 = _normal1;
	this->_normal2 = _normal2;
	//g_printer->printVec("Normal: ", this->_normal);
}


Triangle::~Triangle()
{
}

bool Triangle::intersect(Ray & ray, float * thit, LocalGeo * local)
{
	// Check that the ray is not parallel to plane
	float dot2 = dot(ray._dirn, this->_normal);
	if (dot2 != 0.0f) {
		float dot1 = dot((ray._point - this->_v0), this->_normal);
		float t = -dot1 / dot2;

		// If triangle is behind camera
		if (t < ray._tMin || t > ray._tMax) {
			return false;
		}

		vec3 intPt = ray._point + ray._dirn*t;
		
		//g_printer->printVec("Intersection Pt: ", intPt);

		// This automatically checks if the triangle is in a line
		vec3 edge0 = this->_v1 - this->_v0;
		vec3 edge1 = this->_v2 - this->_v1;
		vec3 edge2 = this->_v0 - this->_v2;
		vec3 vP0 = intPt - this->_v0;
		vec3 vP1 = intPt - this->_v1;
		vec3 vP2 = intPt - this->_v2;

		//g_printer->printVec("edge det: ", vec3(dot(this->_normal, cross(edge0, vP0)), dot(this->_normal, cross(edge1, vP1)), dot(this->_normal, cross(edge2, vP2))));

		// Checks if the intersection point lies in the triangle
		if (dot(this->_normal, cross(edge0, vP0)) >= 0 &&
			dot(this->_normal, cross(edge1, vP1)) >= 0 &&
			dot(this->_normal, cross(edge2, vP2)) >= 0) {
			//float y12 = (this->_v1.y - this->_v2.y);
			//float y02 = (this->_v0.y - this->_v2.y);
			//float x21 = (this->_v2.x - this->_v1.x);
			//float x02 = (this->_v0.x - this->_v2.x);
			//float px2 = (intPt.x - this->_v2.x);
			//float py2 = (intPt.y - this->_v2.y);

			//float w0 = (y12 * px2 + x21 * py2)
			//		  /(y12 * x02 + x21 * y02);

			// Sets the object that thit points to
			*thit  =  t;
			*local = LocalGeo(intPt, this->_normal);
			return true;
		}
	}
	return false;	
}

bool Triangle::intersectP(Ray & ray)
{
	// Check that the ray is not parallel to plane
	float dot2 = dot(ray._dirn, this->_normal);
	if (dot2 != 0.0f) {
		float dot1 = dot((ray._point - this->_v0), this->_normal);
		float t = -dot1 / dot2;

		//g_printer->printFloat("Tri_tMax", ray._tMax);
		// If triangle is behind camera
		if (t < ray._tMin || t > ray._tMax) {
			return false;
		}
		vec3 intPt = ray._point + ray._dirn*t;
		
		//g_printer->printVec("Intersection Pt: ", intPt);

		// This automatically checks if the triangle is in a line
		vec3 edge0 = this->_v1 - this->_v0;
		vec3 edge1 = this->_v2 - this->_v1;
		vec3 edge2 = this->_v0 - this->_v2;
		vec3 vP0 = intPt - this->_v0;
		vec3 vP1 = intPt - this->_v1;
		vec3 vP2 = intPt - this->_v2;

		//g_printer->printVec("edge det: ", vec3(dot(this->_normal, cross(edge0, vP0)), dot(this->_normal, cross(edge1, vP1)), dot(this->_normal, cross(edge2, vP2))));

		// Checks if the intersection point lies in the triangle
		if (dot(this->_normal, cross(edge0, vP0)) >= 0 &&
			dot(this->_normal, cross(edge1, vP1)) >= 0 &&
			dot(this->_normal, cross(edge2, vP2)) >= 0) {
			//cout << "Intersect True \n";
			return true;
		}
	}
	return false;
}

int Triangle::whichShape()
{
	return 2;
}
