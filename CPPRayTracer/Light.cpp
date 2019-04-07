#include "pch.h"
#include "Light.h"


Light::Light()
{
}


Light::~Light()
{
}

Light::Light(vec3 _lightdir, vec3 _color)
{
	this->_lightdir = _lightdir;
	this->_color    = _color;	
}

void Light::generateLightRay(LocalGeo & local, Ray * lray)
{
}
