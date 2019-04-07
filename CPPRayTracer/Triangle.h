#pragma once
#include "Shape.h"

#include "variables.h"

class Triangle :
	public Shape
{
private:
	vec3 _v0;
	vec3 _v1;
	vec3 _v2;
	vec3 _normal;
public:
	Triangle();
	Triangle(vec3 _v0, vec3 _v1, vec3 _v2);
	~Triangle();
	// Test if ray intersects with the shape or not (in object space), if so,
	// return intersection point and normal
	bool intersect(Ray& ray, float* thit, LocalGeo* local) override;

	// Same as intersect, but just return whether there is any intersection or not
	bool intersectP(Ray& ray) override;

	// Returns shape tag (Shape = 0, Sphere = 1, Triangle = 2)
	int whichShape() override;
};

