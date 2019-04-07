#pragma once
#define GLM_FORCE_SWIZZLE
#include <glm.hpp>
using namespace glm;
#include "LocalGeo.h"
#include "Ray.h"
#include "variables.h"

class Transformation
{
public:
	// Class for storing Transformations
	mat4 _transf;
	mat4 _invTransf;

	Transformation();
	Transformation(mat4 _transf);
	~Transformation();

	Ray operator*(Ray secondRay);
	LocalGeo operator*(LocalGeo secondLoc);
};

