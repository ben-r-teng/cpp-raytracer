#pragma once
#include <glm.hpp>
using namespace glm;
#include "LocalGeo.h"
#include "Ray.h"
class Light
{
public:
	vec3 _lightdir;
	vec3 _color;

	Light();
	~Light();
	Light(vec3 _lightdir ,vec3 _color);
	virtual void generateLightRay(LocalGeo& local, Ray *lray) = 0;
};

