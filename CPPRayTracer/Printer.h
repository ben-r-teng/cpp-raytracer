#pragma once
#include <glm.hpp>
#include <string>
using namespace glm;
using namespace std;
#include <iostream>
#include <fstream>
#include "Ray.h"

class Printer
{
public:
	ofstream _myfile;
	Printer();
	~Printer();

	void printVec(string name, vec3 vec);
	void printFloat(string name, float num);
	void printMat(string name, mat4 mat);
	void printRay(string name, Ray ray);


	void close();
};

