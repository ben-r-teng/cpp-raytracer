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

	this->_sampler = Sampler(g_samplesPerPixel, imgDimsX, imgDimsY);
	this->_film = Film(imgDimsX, imgDimsY);

	float fovy = (float(M_PI)) / 180.0f*fovy_in;
	this->_camera = Camera(eyeLoc, g_lookAt, g_upVec, fovy, this->_imgDimsX, this->_imgDimsY);
	this->_raytracer = RayTracer(allPrims);
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
	//may return 0 when not able to detect
	int concurentThreadsSupported = thread::hardware_concurrency()*2;

	if (concurentThreadsSupported > 1 && g_multithreadCPU) {
		cout << "Multithreading Mode Enabled\n";
		cout << "Concurent Threads Supported: " << concurentThreadsSupported << "\n";
		int thread_dimsY = this->_imgDimsY / concurentThreadsSupported;
		vector<thread> threads;
		for (int i = 0; i < concurentThreadsSupported; i++) {
			int startY = thread_dimsY * i;
			int endY = min(this->_imgDimsY, thread_dimsY * (i+1));
			cout << "Start: "<<startY<< " End: " << endY<< "\n";
			//renderThread(startY, endY);

			thread th(&Scene::renderThread, this, startY, endY);
			threads.push_back(move(th));
		}

		for (int i = 0; i < concurentThreadsSupported; i++) {
			threads.at(i).join();
		}
	}
	else {
		while (this->_sampler.getSample(&sample)) {
			if (this->_imgDimsX * this->_imgDimsY * progressBar < pixelsProcessed) {
				cout << round(progressBar * 100.0f) << "% processed\n";
				progressBar += 0.01f;
			}
			pixelsProcessed++;

			ray = this->_camera.generateRay(sample);
			int startingDepth = 0;

			this->_raytracer.trace(ray, startingDepth, refColor);

			this->_film.commit(sample, refColor);
		}
		cout << round(progressBar * 100.0f) << "% processed\n";
	}

	// Completed and now Writing the image
	std::cout << "Writing Image\n";
	_film.writeImage();
	std::cout << "Completed Rendering\n";
}

void Scene::test() {
	cout << "In a thread\n";
}

void Scene::renderThread(int startY, int endY) {
	Sample sample = Sample();
	Color color = Color(0.0f, 0.0f, 0.0f);
	Color& refColor = color;
	Ray ray;
	Sampler threadSampler = Sampler(g_samplesPerPixel, this->_imgDimsX, endY, startY);

	while (threadSampler.getSample(&sample)) {

		ray = this->_camera.generateRay(sample);
		int startingDepth = 0;

		this->_raytracer.trace(ray, startingDepth, refColor);

		this->_film.commit(sample, refColor);
	}
}
