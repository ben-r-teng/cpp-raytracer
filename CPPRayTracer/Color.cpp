#include "pch.h"
#include "Color.h"

// Make val ceiling to 1 then scale to 255b color res
float Color::scaleFloat(float val)
{
	float currVal = val;
	if (currVal > 1.0f) {
		currVal = 1.0f;
	}
	return (currVal *255.0f);
}

Color::Color()
{
}

Color::Color(float _rgb)
{
	this->_r = _rgb;
	this->_g = _rgb;
	this->_b = _rgb;
}

Color::Color(float _r, float _g, float _b)
{
	this->_r = _r;
	this->_g = _g;
	this->_b = _b;
}

Color::Color(vec3 colorVec)
{
	this->_r = colorVec.x;
	this->_g = colorVec.y;
	this->_b = colorVec.z;
}


Color::~Color()
{
}

Color Color::operator+(const Color& b)
{
	Color outColor;
	outColor._r = this->_r + b._r;
	outColor._g = this->_g + b._g;
	outColor._b = this->_b + b._b;
	return outColor;
}

Color Color::operator*(const vec3& b)
{
	Color outColor;
	outColor._r = this->_r * b.x;
	outColor._g = this->_g * b.y;
	outColor._b = this->_b * b.z;
	return outColor;
}
Color Color::scaleColor()
{
	float r = this->scaleFloat(this->_r);
	float g = this->scaleFloat(this->_g);
	float b = this->scaleFloat(this->_b);

	return Color(r, g, b);
}
