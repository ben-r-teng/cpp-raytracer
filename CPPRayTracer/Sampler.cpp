#include "pch.h"
#include "Sampler.h"


Sampler::Sampler()
{
}

Sampler::Sampler(int samplesPerPixel, int imgDimsX, int imgDimsY)
{
	this->_samplesPerPixel = samplesPerPixel;
	this->_imgDimsX        = imgDimsX;
	this->_imgDimsY        = imgDimsY;	

	this->_currPixelCoordX = 0; // Curr Pixel being sampled
	this->_currPixelCoordY = 0;
	this->_pixelsSampled   = 0;
}


Sampler::~Sampler()
{
}

bool Sampler::getSample(Sample * sample)
{
	// std::cout << "Sampler curr x: " << this->_currPixelCoordX << " and sample y: " << this->_currPixelCoordY << "\n";

	// All Samples for this pixel loc acquired
	if(this->_pixelsSampled >= this->_samplesPerPixel){
		// std::cout << "1";
		bool atMaxX = (this->_currPixelCoordX >= this->_imgDimsX - 1);
		bool atMaxY = (this->_currPixelCoordY >= this->_imgDimsY - 1);
		this->_pixelsSampled = 0;
		//std::cout << "this->_currPixelCoordX: " << this->_currPixelCoordX << " this->_currPixelCoordY: " << this->_currPixelCoordY << "\n";
		//std::cout << "atMaxX: " << atMaxX << " atMaxY: " << atMaxY << "\n";

		if(atMaxX && atMaxY){
			// Have gotten all samples
			return false;
		}
		// All Samples gotten for this row (going horizontally then vertically)
		else if(atMaxX){
			this->_currPixelCoordX = 0;
			this->_currPixelCoordY += 1;
		}
		else{
			this->_currPixelCoordX += 1;
		}
	}

	// TODO: For now sample at center of pixel
	// When taking multiple samples use
	*sample = Sample(this->_currPixelCoordX + 0.5f, this->_currPixelCoordY + 0.5f);
	this->_pixelsSampled += 1;
	// std::cout << "3";
	return true;
}
