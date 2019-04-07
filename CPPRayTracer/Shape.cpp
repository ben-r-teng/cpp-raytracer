#include "pch.h"
#include "Shape.h"


Shape::Shape()
{
}


Shape::~Shape()
{
}

bool Shape::intersect(Ray & ray, float * thit, LocalGeo * local)
{
	return false;
}

bool Shape::intersectP(Ray & ray)
{
	cout << "Shape's intersect\n";
	return false;
}

int Shape::whichShape()
{
	return 0;
}
