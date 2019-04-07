#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(vec3 eyeLoc, int imgDimsX, int imgDimsY, float fovy_in, AllPrimitives* allPrims)
{
	this->_eyeLoc = eyeLoc;
	this->_imgDimsX = imgDimsX;
	this->_imgDimsY = imgDimsY;

	int samplesperpixel = 1;
	this->_sampler = Sampler(samplesperpixel, imgDimsX, imgDimsY);
	//this->_film = Film(imgDimsX, imgDimsY);

	float fovy = (float(M_PI)) / 180.0f*fovy_in;
	//this->_camera = Camera(eyeLoc, g_lookAt, g_upVec, fovy, this->_imgDimsX, this->_imgDimsY);
	//this->_raytracer = RayTracer(allPrims);
}


Scene::~Scene()
{
}

// This is the main rendering loop
void Scene::render()
{
	Sample sample = Sample();
	Color color = Color(0.0f, 0.0f, 0.0f);
	Color& refColor = color;
	Ray ray;
	int iter = 0;
	float pixelsProcessed = 0;
	float progressBar = 0;
	std::cout << "Start Rendering\n";
	//while (this->_sampler.getSample(&sample)) {
	//	if (this->_imgDimsX*this->_imgDimsY*progressBar < pixelsProcessed) {
	//		cout << progressBar * 100.0f << "% processed\n";
	//		progressBar += 0.01f;
	//	}
	//	pixelsProcessed++;


	//}
	cout << progressBar * 100.0f << "%d processed\n";
	//std::cout << "Writing Image\n";
	std::cout << "Completed Rendering\n";
}
