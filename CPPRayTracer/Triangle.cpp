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

		float paraU = dot(cross(intPt - this->_v0, this->_v2 - this->_v0), this->_normal);
		
		if (paraU < 0) {
			return false;
		}
		float paraV = dot(cross(intPt - this->_v1, this->_v0 - this->_v1), this->_normal);
		if (paraV < 0) {
			return false;
		}
		float paraW = dot(cross(intPt - this->_v2, this->_v1 - this->_v2), this->_normal);
		if (paraW < 0) {
			return false;
		}
		
		float paraArea = dot(cross((this->_v1 - this->_v0), (this->_v2 - this->_v0)), this->_normal);
		float weightU = paraU/paraArea;
		float weightV = paraV/paraArea;
		float weightW = paraW/paraArea;

		*thit = t;
		vec3 interpNormal = weightW * this->_normal0 + weightU * this->_normal1 + weightV * this->_normal2;
		
		// If option set, use interpolated normal
		if (g_vertexNormalInterp) {
			*local = LocalGeo(intPt, interpNormal);
		}
		// If not, use normal calculated by vertices of triangle
		else {
			*local = LocalGeo(intPt, this->_normal);
		}
		return true;
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
