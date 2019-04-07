#include "pch.h"
#include "GeoPrimitive.h"


GeoPrimitive::GeoPrimitive()
{
}


GeoPrimitive::~GeoPrimitive()
{
	delete this->_shape;
	delete this->_material;
}

GeoPrimitive::GeoPrimitive(Shape * _shape, Material * _material, mat4 _objToWorld)
{
	this->_shape = _shape;
	this->_material = _material;
	this->_objToWorld = Transformation(_objToWorld);

	// TODO: Review inverse transformations
	this->_worldToObj = Transformation(inverse(_objToWorld));
}

bool GeoPrimitive::intersect(Ray & ray, float* thit, Intersection * in)
{
	Ray oray = this->_worldToObj*ray;
	Shape* currShape = (this->_shape);
	float currHit = g_tMax;
	LocalGeo currLocal = LocalGeo(vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	if (currShape != NULL) {
		//If there is an intersection
		if ((currShape->intersect(oray, &currHit, &currLocal))) {
			*thit = currHit;
			currLocal = this->_objToWorld*currLocal;
			currLocal._normal = normalize(currLocal._normal);
			*in = Intersection(currLocal, this);
			return true;
		}
	}
	return false;
}

bool GeoPrimitive::intersectP(Ray & ray)
{
	Ray oray = this->_worldToObj*ray;
	Shape* currShape = (this->_shape);
	float currHit = g_tMax;
	LocalGeo currLocal = LocalGeo(vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	if (currShape != NULL) {
		//If there is an intersection
		if ((currShape->intersectP(oray))) {
			return true;
		}
	}
	return false;
}

//void GeoPrimitive::getBRDF(LocalGeo & local, BRDF* brdf)
void GeoPrimitive::getBRDF(BRDF* brdf)
{
	//this->_material->getBRDF(local, brdf);
	this->_material->getBRDF(brdf);
}
