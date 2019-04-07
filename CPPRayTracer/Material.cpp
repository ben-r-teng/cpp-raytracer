#include "pch.h"
#include "Material.h"
#include "LocalGeo.h"


Material::Material()
{
	this->_constBRDF = BRDF();
}

Material::Material(BRDF constBRDF)
{
	this->_constBRDF = constBRDF;
}


Material::~Material()
{
}

//void Material::getBRDF(LocalGeo& local, BRDF* brdf)
void Material::getBRDF(BRDF* brdf)
{
	//For now, we will have constant BRDF for all location,
	//TODO: Vary BRDF based on texture map location
	*brdf = this->_constBRDF;
}

