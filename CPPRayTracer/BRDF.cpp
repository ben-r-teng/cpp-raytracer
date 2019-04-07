#include "pch.h"
#include "BRDF.h"


BRDF::BRDF()
{
	this->_kd  = vec3(0.0f);
	this->_ksp = vec3(0.0f);
	this->_ka  = vec3(0.2f);
	this->_ke  = vec3(0.0f);
	this->_ksh = 1.0f;
}

// Diffuse, specular, ambient, and mirror_reflction
// Ambient          => _ka
// Diffuse          => _kd
// Specular         => _ksp
// emission         => _ke
// Shininess        => _ksh

BRDF::BRDF(vec3 _ka,  float _ksh, vec3 _kd, vec3 _ksp, vec3 _ke)
{
	this->_kd  = _kd; 
	this->_ksp = _ksp; 
	this->_ka  = _ka; 
	this->_ke  = _ke; 
	this->_ksh = _ksh; 	
}


BRDF::~BRDF()
{
}
