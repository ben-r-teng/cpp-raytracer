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
	int concurentThreadsSupported = thread::hardware_concurrency();

	if (concurentThreadsSupported > 1 && g_multithreadCPU) {
		cout << "Multithreading Mode Enabled\n";
		cout << "Concurent Threads Supported: " << concurentThreadsSupported << "\n";
		int thread_dimsY = this->_imgDimsY / concurentThreadsSupported;
		for (int i = 0; i < concurentThreadsSupported; i++) {
			float yStart = thread_dimsY * i;
			float yEnd = min(this->_imgDimsY, thread_dimsY * (i+1));
			
//			renderThread();

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
	}

	// Completed and now Writing the image
	cout << round(progressBar * 100.0f) << "% processed\n";
	std::cout << "Writing Image\n";
	_film.writeImage();
	std::cout << "Completed Rendering\n";
}

/*
void Scene::renderThread() {
	Sample sample = Sample();
	Color color = Color(0.0f, 0.0f, 0.0f);
	Color& refColor = color;
	Ray ray;
	Sampler threadSampler = Sampler(samplesperpixel, imgDimsX, imgDimsY);

	while (threadSampler.getSample(&sample)) {
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
}
*/