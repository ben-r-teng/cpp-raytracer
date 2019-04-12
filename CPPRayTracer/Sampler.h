#include "Sample.h"
#include <iostream>

#pragma once
class Sampler
{
private:
	int _currPixelCoordX; // Curr Pixel being sampled
	int _currPixelCoordY;
	int _pixelsSampled;

public:
	int _samplesPerPixel;
	int _imgDimsX; // Pixel dimenstions of output image
	int _imgDimsY; // Pixel dimenstions of output image	

	Sampler();
	Sampler(int samplesPerPixel, int imgDimsX, int imgDimsY);
	Sampler(int samplesPerPixel, int imgDimsX, int imgDimsY, int _currPixelCoordY);
	~Sampler();
	bool getSample(Sample * sample); // Pass in pointer, modify pointed to sample; Return false if no samples left
};

