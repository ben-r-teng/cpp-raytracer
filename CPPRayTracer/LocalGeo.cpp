#include "pch.h"
#include "LocalGeo.h"


LocalGeo::LocalGeo()
{
}

LocalGeo::LocalGeo(vec3 _pos, vec3 _normal)
{
	this->_pos    = _pos; 
	this->_normal = _normal; 	
}


LocalGeo::~LocalGeo()
{
}
