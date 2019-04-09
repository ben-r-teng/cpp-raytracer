#include "pch.h"
#include "DirnLight.h"


DirnLight::DirnLight()
{
}


DirnLight::~DirnLight()
{
}

DirnLight::DirnLight(vec3 _lightdir, vec3 _color)
{
	this->_lightdir = normalize(_lightdir);
	this->_color = _color;
}

void DirnLight::generateLightRay(LocalGeo & local, Ray * lray)
{
	//float t_max = length(this->_lightdir - local._pos);
	//vec3 ray_dirn = normalize(this->_lightdir - local._pos);
	//g_printer->printVec("ray_dirn", ray_dirn);
	// origin, dirn, tmin, tmax
	*lray = Ray(local._pos, this->_lightdir, g_tMin, g_tMax);
	//*lray = Ray(local._pos, ray_dirn, g_tMin, g_tMax);
}
