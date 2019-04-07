#pragma once
#include "Ray.h"
#include "Color.h"
#include <iostream>
#include "AllPrimitives.h"
using namespace std;

class RayTracer
{
private:
	AllPrimitives* _allPrimRef;
public:
	RayTracer();
	RayTracer(AllPrimitives* _allPrimRef);
	~RayTracer();
	void trace(Ray& ray, int depth, Color& color);
	Color shading(Intersection intPoint, Light* currLight, Ray lray, Ray objRay);
	Ray createReflectRay(Intersection * intPoint, Ray & ray);
};

