#pragma once
#include "Ray.h"
#include "LocalGeo.h"
#include <iostream>
using namespace std;


// Abstract class
class Shape
{
public:
	Shape();
	~Shape();
	// Test if ray intersects with the shape or not (in object space), if so,
	// new values if thit is lower than the existing one
	virtual bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;

	// Same as intersect, but just return whether there is any intersection or not
	virtual bool intersectP(Ray& ray) = 0;
	virtual int whichShape();
};

