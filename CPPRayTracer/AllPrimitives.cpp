#include "pch.h"
#include "AllPrimitives.h"


AllPrimitives::AllPrimitives()
{
}

AllPrimitives::AllPrimitives(vector<GeoPrimitive*> _primList)
{
	this->_primList = _primList;
}


AllPrimitives::~AllPrimitives()
{
	for (vector<GeoPrimitive*>::iterator it = this->_primList.begin(); it != this->_primList.end(); ++it) {
		delete(*it);
	}
	for (vector<Light*>::iterator its = this->_lights.begin(); its != this->_lights.end(); ++its) {
		delete(*its);
	}
}

// Intersection
// 	LocalGeo _localGeo;
// 	GeoPrimitive* _geoPrimitive;

// Check if any of the Primitives are intersected by the ray
// No intersection => thit not modified, in not modified
// Intersection    => thit modified, in modified
bool AllPrimitives::intersect(Ray & ray, float * thit, Intersection * in)
{

	bool isIntersect = false;
	*thit = g_tMax;
	Intersection temp_in;
	// Material currMat = Material();

	// Check if there are any primitives
	if (this->_primList.size()>0) {
		// Iterate through all the primitives
		for (size_t i = 0; i < this->_primList.size(); i++) {
			GeoPrimitive* geoPrim = (this->_primList.at(i));
			float currHit = g_tMax;
			//LocalGeo currLocal = LocalGeo(vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
			if (geoPrim != NULL) {
				//If there is an intersection
				//if ((geoPrim->intersect(ray, &currHit, &currLocal))) {
				if ((geoPrim->intersect(ray, &currHit, &temp_in))) {
					//isIntersect = true;
					//vec3 kaVec = in->_geoPrimitive->_material->_constBRDF._ka;
					//cout << "KA: " << kaVec.x << " " << kaVec.y << " " << kaVec.z << "\n";

					// Replace current if true
					if (currHit < *thit && currHit > g_tMin) {
						*thit = currHit;
						//temp_in._localGeo._normal.x = 1;
						*in = Intersection(temp_in._localGeo, this->_primList.at(i));
						isIntersect = true;
						//cout << " allPrim " << in->_geoPrimitive->_shape->whichShape() << "local: " << temp_in._localGeo._normal.x 
						//	<< " " << temp_in._localGeo._normal.y << " " << temp_in._localGeo._normal.z << " currHit: "
						//	<< *thit << "\n";
					}
				}
			}
		}

	}

	return isIntersect;
}

bool AllPrimitives::intersectP(Ray & ray)
{	
	// Check if there are any primitives
	if (this->_primList.size() > 0) {
		// Iterate through all the primitives
		for (size_t i = 0; i < this->_primList.size(); i++) {
			GeoPrimitive* geoPrim = (this->_primList.at(i));
			if (geoPrim != NULL) {
				//If there is an intersection
				if ((geoPrim->intersectP(ray))) {
					//g_printer->printFloat("Light Intersect", i);
					return true;
					//return false;
				}
			}
		}
	}
	return false;
}
