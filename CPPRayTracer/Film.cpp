#include "pch.h"
#include "Film.h"
#include <string>

Film::Film()
{
}

Film::Film(int _imgDimsX, int _imgDimsY)
{
	this->_imgDimsX = _imgDimsX;
	this->_imgDimsY = _imgDimsY;

	Color initColor = Color(0.0f, 0.0f, 0.0f);

	this->_colors           = vector<Color>(_imgDimsX*_imgDimsY, initColor);
	this->_samplesPerBucket = vector<int>(_imgDimsX*_imgDimsY, 0);
}


Film::~Film()
{
}

void Film::commit(Sample sample, Color color)
{
	int pixelX = int(sample._x);
	int pixelY = int(sample._y);
	//cout << "Colors size: " << this->_colors.size() << "\n";

	int index = pixelX + this->_imgDimsX * pixelY;

	this->_colors.at(index) = this->_colors.at(index) + color.scaleColor();
	this->_samplesPerBucket.at(index) += 1;
}

void Film::writeImage()
{
	int w = this->_imgDimsX;
	int h = this->_imgDimsY;
	int pix = w * h;
	BYTE *pixels = new BYTE[3 * pix];
	
	//char ch;
	//std::cout << "Pixels: " << pix << " size of colors: " << to_string(this->_colors.size()) << "\n" ;
	//
	//cout << "Pause\n";
	//cin >> ch;

	for (int i = 0; i < pix; i++) {
		//std::cout << "i: " << i << "\n";
		//cin >> ch;
		if(this->_samplesPerBucket.at(i) == 0){
			// To catch divide by 0 bugs
			std::cout << "ERROR: Pixels Index: " << i << " has no samples" << "\n" ;
			pixels[i*3 + 0] = BYTE(0.0f);
			pixels[i*3 + 1] = BYTE(0.0f);
			pixels[i*3 + 2] = BYTE(0.0f);
		} 
		else {
			pixels[i*3 + 0] = BYTE(this->_colors.at(i)._b / (this->_samplesPerBucket.at(i)));
			pixels[i*3 + 1] = BYTE(this->_colors.at(i)._g / (this->_samplesPerBucket.at(i)));
			pixels[i*3 + 2] = BYTE(this->_colors.at(i)._r / (this->_samplesPerBucket.at(i))); 
		}
	}
	string fname = g_outName;
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);

	std::cout << "Saving screenshot: " << fname << "\n";

	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
	delete pixels;
}

void Film::printFilm()
{
	std::cout << "Printing Start\n";
	string colorprint, samplesprint;
	for (int i = 0; i < this->_imgDimsX; i++) {
		for (int j = 0; j < this->_imgDimsY; j++) {
			colorprint += "Pixel Loc: " + to_string(i)
				+ " " + to_string(j)
				+ " R: " + to_string(this->_colors[i + this->_imgDimsY*j]._r)
				+ " G: " + to_string(this->_colors[i + this->_imgDimsY*j]._g)
				+ " B: " + to_string(this->_colors[i + this->_imgDimsY*j]._b)
				+ "\n";
			samplesprint += "Pixel Loc: " + to_string(i)
				+ " " + to_string(j)
				+ " SamplesPerBucket: " + to_string(this->_samplesPerBucket[i + this->_imgDimsY*j])
				+ "\n";
		}
	}
	std::cout << colorprint;
	std::cout << samplesprint;
	std::cout << "Printing Complete\n";
}

