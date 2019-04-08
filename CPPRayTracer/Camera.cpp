#include "pch.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(vec3 _lookFrom, vec3 _lookAt, vec3 _upVec, float _fovy, int _imgDimsX, int _imgDimsY)
{
	this->_lookFrom = _lookFrom;
	this->_lookAt   = _lookAt;
	this->_upVec    = _upVec;
	this->_fovy     = _fovy;	
	// assume image plane is 1 unit away from camera
	this->_height = 2 * tan(_fovy / 2);
	this->_width 	= float(_imgDimsX)/float(_imgDimsY)*this->_height;

	this->_imgDimsX = _imgDimsX;
	this->_imgDimsY = _imgDimsY;

	//private vars
	vec3 a = this->_lookFrom - this->_lookAt;
	vec3 b = this->_upVec;

	//g_printer->printVec("LookVec: ", a);
	//g_printer->printVec("UpVec: ", b);


	//Make Coord Frame
	this->_w = normalize(a);
	this->_u = normalize(cross(b, this->_w));
	this->_v = cross(this->_w, this->_u);
	// print vector
	//cout << "w: " << this->_w.x << " "
	// 			  << this->_w.y << " "
	// 			  << this->_w.z << "\n";
	//cout << "u: " << this->_u.x << " "
	// 			  << this->_u.y << " "
	// 			  << this->_u.z << "\n";
	//cout << "v: " << this->_v.x << " "
	// 			  << this->_v.y << " "
	// 			  << this->_v.z << "\n";
	//cout << " width height: " << this->_width << " " << this->_height << "\n ";

}


Camera::~Camera()
{
}

// TODO: Can optimize by making Coord Frame in object init
// since it doesnt change
Ray Camera::generateRay(Sample sample)
{
	// Scaled from 0 to 1
	float x = (sample._x/(float (this->_imgDimsX)))*this->_width;
	float y = (sample._y/(float (this->_imgDimsY)))*this->_height;

	float alpha = (this->_width/2) * (x - this->_width/2)/(this->_width/2);
	float beta  = (this->_height/2)*(this->_height / 2 - y) / (this->_height / 2);

	 //cout << "sample: " << x << " " << y 
	 //<< "alpha: " << alpha << " beta: " << beta << 
	 //" x_scale: " << (x - this->_width / 2) / (this->_width / 2) <<
	 //" y_scale: " << (this->_height / 2 - y) / (this->_height / 2) <<
	 //	"\n";

	vec3 rayDirn = normalize(alpha * this->_u + beta * this->_v - this->_w);

	Ray outRay = Ray(this->_lookFrom, rayDirn, g_tMin, g_tMax);
	return outRay;
}
