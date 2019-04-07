#pragma once
#ifndef __INTERSECTION__
#define __INTERSECTION__

#include "LocalGeo.h"
//#include "GeoPrimitive.h"

class GeoPrimitive;

class Intersection
{
public:
	LocalGeo _localGeo;
	GeoPrimitive* _geoPrimitive;

	Intersection();
	~Intersection();
	Intersection(LocalGeo _localGeo, GeoPrimitive* _geoPrimitive);	
};

#endif