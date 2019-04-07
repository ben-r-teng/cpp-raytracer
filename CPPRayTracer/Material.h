#pragma once
#include "BRDF.h"
#include "LocalGeo.h"
class Material
{
public:
	// Class for storing material
	// Will be useful for supporting texture maps that vary BRDFs by location
	BRDF _constBRDF;

	Material();
	Material(BRDF constBRDF);
	~Material();
	//void getBRDF(LocalGeo& local, BRDF* brdf);
	void getBRDF(BRDF* brdf);
};

