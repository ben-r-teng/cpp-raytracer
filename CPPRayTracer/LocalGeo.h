#pragma once
#include <glm.hpp>
using namespace glm;

class LocalGeo
{
public:
	vec3 _pos;
	vec3 _normal;

	LocalGeo();
	LocalGeo(vec3 _pos, vec3 _normal);
	~LocalGeo();
};

