#pragma once
#include "Light.h"
#include "variables.h"
class PointLight :
	public Light
{
public:
	PointLight();
	~PointLight();
	PointLight(vec3 _lightdir, vec3 _color);
	void generateLightRay(LocalGeo& local, Ray *lray) override;

};

