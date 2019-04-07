#pragma once
#include "Sample.h"
#include "Ray.h"
#include "variables.h"
#include <iostream>
using namespace std;
#include "Printer.h"

class Camera
{
private:
	vec3 _w;
	vec3 _u;
	vec3 _v;
public:
	vec3 _lookFrom;
	vec3 _lookAt;
	vec3 _upVec;
	float _fovy;

	float _width;
	float _height;
	int _imgDimsX;
	int _imgDimsY;

	Camera();
	Camera(vec3 _lookFrom, vec3 _lookAt, vec3 _upVec, float _fovy, int _imgDimsX, int _imgDimsY);
	~Camera();
	Ray generateRay(Sample sample);
};

