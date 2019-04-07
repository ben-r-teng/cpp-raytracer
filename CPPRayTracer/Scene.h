#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Sampler.h"
#include "Sample.h"
#include <iostream>
#include "Film.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "variables.h"
#include "AllPrimitives.h"
#include "Printer.h"
#include "Color.h"

using namespace glm;

class Scene
{
private:
	vec3 _eyeLoc; // eye location
	int _imgDimsX; // Pixel dimenstions of output image
	int _imgDimsY; // Pixel dimenstions of output image

	Sampler _sampler;
	Film _film;
	Camera _camera;
	RayTracer _raytracer;


public:
	Scene();
	Scene(vec3 eyeLoc, int imgDimsX, int imgDimsY, float fovy_in, AllPrimitives* allPrims);
	~Scene();
	void render(); // Main rendering loop
};