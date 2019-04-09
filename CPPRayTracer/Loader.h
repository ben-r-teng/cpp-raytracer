#pragma once

//#include "AllPrimitives.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include <tiny_obj_loader.h>
#include <iostream>
#include "AllPrimitives.h"
#include "Triangle.h"


using namespace std;
using namespace tinyobj;


void readfile(string filename, string mtlPath, AllPrimitives& allPrims);
//void readfile();
void printRealVector(string name, vector<real_t> vert);

