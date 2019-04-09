#include "pch.h"
#include "PointLight.h"


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

PointLight::PointLight(vec3 _lightdir, vec3 _color)
{
	this->_lightdir = _lightdir;
	this->_color = _color;
}

void PointLight::generateLightRay(LocalGeo & local, Ray * lray)
{
	float t_max = length(this->_lightdir - local._pos);
	vec3 ray_dirn = normalize(this->_lightdir - local._pos);
	//g_printer->printVec("ray_dirn", ray_dirn);
	// origin, dirn, tmin, tmax
	*lray = Ray(local._pos, ray_dirn, g_tMin, t_max);
	//*lray = Ray(local._pos, ray_dirn, g_tMin, g_tMax);
}
