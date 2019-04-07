#include "pch.h"
#include "Intersection.h"


Intersection::Intersection()
{
}


Intersection::~Intersection()
{
}

Intersection::Intersection(LocalGeo _localGeo, GeoPrimitive * _geoPrimitive)
{
	this->_localGeo     = _localGeo;
	this->_geoPrimitive = _geoPrimitive;
}
