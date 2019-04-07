#pragma once
#include <glm.hpp>
using namespace glm;
class BRDF
{
public:
	// Diffuse, specular, ambient, and mirror reflction
	vec3 _kd, _ksp, _ka, _ke;
	float _ksh;
	BRDF();
	BRDF(vec3 _ka, float _ksh, vec3 _kd, vec3 _ksp,  vec3 _ke);
	~BRDF();
};

