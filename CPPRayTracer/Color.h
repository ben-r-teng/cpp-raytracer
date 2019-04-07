#pragma once
#include <glm.hpp>
using namespace glm;
class Color
{
private:
	// Make val ceiling to 1 then scale to 255b color res
	float scaleFloat(float val);
public:
	// Range btw 0-1
	float _r, _g, _b;
	Color();
	Color(float _rgb);
	Color(float _r, float _g, float _b);
	Color(vec3 colorVec);
	~Color();
	Color operator+(const Color&);
	Color operator*(const vec3&);

	// Make color ceiling to 1 then scale to 255b color res
	Color scaleColor();
};

