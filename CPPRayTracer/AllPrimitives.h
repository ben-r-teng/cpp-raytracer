#pragma once
#include <vector> 
#include "GeoPrimitive.h"
#include "Intersection.h"
#include "Ray.h"
#include "variables.h"
#include "Light.h"

using namespace std;
class AllPrimitives
{
public:
	vector<GeoPrimitive*> _primList;
	vector<Light*> _lights;

	AllPrimitives();
	AllPrimitives(vector<GeoPrimitive*> _primList);
	~AllPrimitives();

	bool intersect(Ray& ray, float* thit, Intersection* in);
	// Same as intersect, but just return whether there is any intersection or not
	bool intersectP(Ray& ray);
};

