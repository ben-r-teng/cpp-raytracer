#include "pch.h"
#include "Printer.h"


Printer::Printer()
{
	this->_myfile.open("cout.txt");
}


Printer::~Printer()
{
}

void Printer::printVec(string name, vec3 vec)
{
	this->_myfile << name << ": " << vec.x << " " << vec.y << " " << vec.z << "\n";
}

void Printer::printFloat(string name, float num)
{
	this->_myfile << name << ": " << num << "\n";
}

void Printer::printMat(string name, mat4 mat)
{
	this->_myfile << name << ":\n" 
	<< mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << " " << mat[0][3] << "\n"
	<< mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << " " << mat[1][3] << "\n"
	<< mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << " " << mat[2][3] << "\n"
	<< mat[3][0] << " " << mat[3][1] << " " << mat[3][2] << " " << mat[3][3] << "\n";
}

void Printer::printRay(string name, Ray ray)
{
	this->_myfile << name << ": Point: " << ray._point.x << " " << ray._point.y << " " << ray._point.z
				  		 << " // Dirn: " << ray._dirn.x  << " " << ray._dirn.y  << " " << ray._dirn.z
				  		  << " // tMin: "<< ray._tMin 
				  		  << " // tMax: "<< ray._tMax << "\n"; 
}

void Printer::close()
{
	this->_myfile.close();
}
