#include "pch.h"
#include "Ray.h"


Ray::Ray()
{
}

Ray::Ray(vec3 _point, vec3 _dirn, float _tMin, float _tMax)
{
	this->_point = _point;
	this->_dirn  = _dirn;
	this->_tMin  = _tMin;
	this->_tMax  = _tMax;
}

Ray::~Ray()
{
}
