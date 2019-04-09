#pragma once
#include "Light.h"
#include "variables.h"
class DirnLight :
	public Light
{
public:
	DirnLight();
	~DirnLight();
	DirnLight(vec3 _lightdir, vec3 _color);
	void generateLightRay(LocalGeo& local, Ray *lray) override;
};

