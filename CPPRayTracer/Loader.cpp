#include "pch.h"
#include "Loader.h"

void readfile()
{
	string inputfile = "../Graphics/basic_test.obj";
	tinyobj::attrib_t attrib;
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;

	string warn;
	string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

	cout << "Load file successful: " + inputfile + " " << boolalpha << ret << " \n";
}
