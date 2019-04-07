#include "pch.h"
#include "RayTracer.h"
#include "variables.h"

RayTracer::RayTracer()
{
	//this->_sphere = Sphere(vec3(0.0f, 0.0f, -2.0f), 1.0f);
}

RayTracer::RayTracer(AllPrimitives* _allPrimRef)
{
	this->_allPrimRef = _allPrimRef;
}


RayTracer::~RayTracer()
{
}

// Output is Color
void RayTracer::trace(Ray& ray, int depth, Color& color)
{
	//cout << "depth: " << depth << "\n";

	if (depth >= g_maxRecDepth) {
		//cout << "max depth: " << depth << "\n";

		color = Color(0.0f, 0.0f, 0.0f);
		return;
	}
	float thit;
	Intersection intPoint;
	// bool intersect(Ray& ray, float* thit, Intersection* in)     
	if(!(this->_allPrimRef->intersect(ray, &thit, &intPoint))) {
		//g_printer->printVec("Ray ", ray._point);
		// No intersection
		color = Color(0.0f, 0.0f, 0.0f);
		return;
	}

	BRDF currBRDF;
	// Obtain the brdf at intersection point
	intPoint._geoPrimitive->getBRDF(&currBRDF);

	//color = Color(currBRDF._ka.x * 255.0f, currBRDF._ka.y * 255.0f, currBRDF._ka.z * 255.0f);
	color = Color(currBRDF._ka) + Color(currBRDF._ke);

	//// There is an intersection, loop through all light source
	for (size_t i = 0; i < this->_allPrimRef->_lights.size(); i++) {
		Ray lray;
		this->_allPrimRef->_lights.at(i)->generateLightRay(intPoint._localGeo, &lray);
		
		//g_printer->printFloat("tMax", lray._tMax);

		// If light is not blocked, no intersection
		if (!(this->_allPrimRef->intersectP(lray))) {
			color = color + this->shading(intPoint, this->_allPrimRef->_lights.at(i), lray, ray);
		}
		//else {
		//	color = Color(1.0f);
		//}
	}

	//// Handle mirror reflection
	Ray reflectRay = createReflectRay(&intPoint, ray);

	Color tempColor = Color(0.0f, 0.0f, 0.0f);
	Color& colorRef = tempColor;
	// Make a recursive call to trace the reflected ray
	trace(reflectRay, depth + 1, colorRef);
	//color = color + colorRef * vec3(0.5f);
	color = color + colorRef * currBRDF._ksp;

	return;
}

// lray = light ray from intersection to light source
// objRay = ray from intersection point to previous origin
Color RayTracer::shading(Intersection intPoint, Light* currLight, Ray lray, Ray objRay)
{
	BRDF currBRDF;
	intPoint._geoPrimitive->getBRDF(&currBRDF);
	float attenuation = 0;
	// if point
	if (lray._tMax < g_tMax) {
		attenuation = 1.0f / (g_kConst + g_kLin * lray._tMax + g_kQuad * pow(lray._tMax, 2));
	}
	// if directional
	else {
		attenuation = 1.0f / (g_kConst);
	}
	float nDotL = dot(intPoint._localGeo._normal, lray._dirn);
	vec3 diffuse = currBRDF._kd  * max(nDotL, 0.0f);

	vec3 halfvec = normalize(lray._dirn + (objRay._dirn * -1.0f));
	float nDotH = dot(intPoint._localGeo._normal, halfvec);
	vec3 specular = currBRDF._ksp * currLight->_color * pow(max(nDotH, 0.0f), currBRDF._ksh);

	Color totColor = attenuation * currLight->_color * (specular + diffuse);

	return totColor;
}

//	reflectRay  = createReflectRay(in.local, ray);
// Calculate the Reflection
Ray RayTracer::createReflectRay(Intersection* intPoint, Ray& ray) {
	vec3 refl = ray._dirn - 2 * dot(ray._dirn, intPoint->_localGeo._normal) * intPoint->_localGeo._normal;

	return Ray(intPoint->_localGeo._pos, refl, g_tMin, g_tMax);
}
