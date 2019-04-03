#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace glm;

class Scene
{
private:
	vec3 _eyeLoc; // eye location
	int _imgDimsX; // Pixel dimenstions of output image
	int _imgDimsY; // Pixel dimenstions of output image

public:
	Scene();
	~Scene();
	void render(); // Main rendering loop
};