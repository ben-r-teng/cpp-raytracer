#pragma once
#ifndef __GEO_PRIMITIVE__
#define __GEO_PRIMITIVE__

#include "Shape.h"
#include "Material.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "BRDF.h"
#include "variables.h"
#include "Intersection.h"
#include "Transformation.h"


// To get around circular dependency with Intersection
//class Intersection;
//#include "Intersection.h"

class GeoPrimitive
{
public:
	// TODO: Not sure if this is needed
	Transformation _objToWorld;
    Transformation _worldToObj;
	Shape* _shape;
	 Material* _material;

	GeoPrimitive();
	~GeoPrimitive();

	GeoPrimitive(Shape* _shape, Material* _material, mat4 _objToWorld);

	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	//void getBRDF(LocalGeo& local, BRDF* brdf);
	void getBRDF(BRDF* brdf);
};

#endif