#pragma once
#include <glm.hpp>
using namespace glm;

class Ray
{
public:
	vec3 _point;
	vec3 _dirn;
	float _tMin;
	float _tMax;
	Ray();
	Ray(vec3 _point, vec3 _dirn, float _tMin, float _tMax);
	~Ray();
};

