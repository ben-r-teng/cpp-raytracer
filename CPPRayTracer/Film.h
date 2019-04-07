#include "Sample.h"
#include "Color.h"
#include <iostream>
#include <vector> 
#include <FreeImage.h>
#include "variables.h"

using namespace std;

#pragma once
class Film
{
private:
	int _imgDimsX; // Pixel dimenstions of output image
	int _imgDimsY; // Pixel dimenstions of output image
	
	// Store a color for every pixel
	// Sum of all colors in bucket to be divided by the samples per bucket at end
	vector<Color> _colors;
	// Samples per bucket used to avg
	vector<int> _samplesPerBucket;

public:
	Film();
	Film(int _imgDimsX, int _imgDimsY);
	~Film();
	void commit(Sample sample, Color color); // Will write the color to (sample.x, sample.y) on the image
	void writeImage(); // Output image to a file
	void printFilm(); // Debug Statement to print color and samplesperbucket
};

