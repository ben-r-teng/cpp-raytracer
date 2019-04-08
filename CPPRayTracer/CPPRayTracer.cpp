// CPPRayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include <FreeImage.h>

#include "Loader.h"
#include "Scene.h"
#include "Triangle.h"

using namespace std;

int main()
{
	clock_t t1, t2;
	t1 = clock();
	FreeImage_Initialise();
	std::cout << "Raytracer Start\n";
	vector<GeoPrimitive*> primitives;
	AllPrimitives allPrims = AllPrimitives(primitives);

	readfile("../Graphics/simple.obj", allPrims);
	
	// Test Image
	g_imgdimsx = 640;
	g_imgdimsy = 480;

	g_lookFrom.x = 0;
	g_lookFrom.y = 0;
	g_lookFrom.z = 0;

	g_lookAt.x   = 0;
	g_lookAt.y   = -1;
	g_lookAt.z   = 0;

	g_upVec.x    = 1;
	g_upVec.y    = 0;
	g_upVec.z    = 0;
	g_fovy       = 30;

	//BRDF currBRDF = BRDF();
	//currBRDF = BRDF(vec3(1, 0, 0), currBRDF._ksh, currBRDF._kd, currBRDF._ksp, currBRDF._ke);
	//int maxverts = 4;
	//vector<vec3> vertices;
	//vertices.push_back(vec3(-1, -1, 0));
	//vertices.push_back(vec3( 1, -1, 0));
	//vertices.push_back(vec3( 1,  1, 0));
	//vertices.push_back(vec3(-1, +1, 0));

 //   Triangle * triangle = new Triangle(vertices.at(0), vertices.at(1), vertices.at(2));
	//Shape * shape = triangle;
	//Material* currMat = new Material(currBRDF);
	//GeoPrimitive* geoPrim = new GeoPrimitive(shape, currMat, mat4(1.0));
	//allPrims._primList.push_back(geoPrim);

 //   Triangle * triangle2 = new Triangle(vertices.at(0), vertices.at(1), vertices.at(2));
	//Shape * shape2 = triangle2;
	//Material* currMat2 = new Material(currBRDF);
	//GeoPrimitive* geoPrim2 = new GeoPrimitive(shape2, currMat2, mat4(1.0));
	//allPrims._primList.push_back(geoPrim2);


	Scene main_scene = Scene(g_lookFrom, g_imgdimsx, g_imgdimsy, g_fovy, &allPrims);
	main_scene.render();


	FreeImage_DeInitialise();
	t2 = clock();
	cout << "Ran for " << (((float)t2 - (float)t1) / CLOCKS_PER_SEC) << " seconds" << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
