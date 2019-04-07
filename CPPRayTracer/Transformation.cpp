#include "pch.h"
#include "Transformation.h"


Transformation::Transformation()
{
}

Transformation::Transformation(mat4 _transf)
{
	this->_transf = _transf;
	// How do we guarantee that there is an inverse?
	this->_invTransf = transpose(inverse(_transf));
}


Transformation::~Transformation()
{
}


Ray Transformation::operator*(Ray secondRay)
{
	Ray ray = Ray(vec3(0.0f), vec3(0.0f), secondRay._tMin, secondRay._tMax);
	ray._point = (this->_transf*vec4(secondRay._point, 1.0f)).xyz();
	ray._dirn = (this->_transf*vec4(secondRay._dirn, 0.0f)).xyz();
	return ray;
}

LocalGeo Transformation::operator*(LocalGeo secondLoc)
{
	LocalGeo locGeo = LocalGeo(vec3(0.0f), vec3(0.0f));
	locGeo._pos = (this->_transf * vec4(secondLoc._pos, 1.0f)).xyz();
	locGeo._normal = (this->_invTransf * vec4(secondLoc._normal, 0.0f)).xyz();

	return locGeo;
}