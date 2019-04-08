#include "pch.h"
#include "Loader.h"

void readfile(string filename, AllPrimitives& allPrims)
{
	tinyobj::attrib_t attrib;
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;

	string warn;
	string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());

	printRealVector("vertices",  attrib.vertices);
	printRealVector("normals",   attrib.normals);
	printRealVector("texcoords", attrib.texcoords);
	printRealVector("colors",    attrib.colors);

	for (int i = 0; i < shapes.size(); i++) {
		cout << shapes[i].name + "\n";
		cout << "Vertex Ind: \n";
		for (int j = 0; j < shapes[i].mesh.indices.size(); j++) {
			cout << shapes[i].mesh.indices[j].vertex_index << "\n";
		}

		BRDF currBRDF = BRDF();
		currBRDF = BRDF(vec3(.5, 0, .5), currBRDF._ksh, currBRDF._kd, currBRDF._ksp, currBRDF._ke);

		vec3 v0 = vec3(attrib.vertices[shapes[i].mesh.indices[0].vertex_index * 3 + 0],
					   attrib.vertices[shapes[i].mesh.indices[0].vertex_index * 3 + 1],
					   attrib.vertices[shapes[i].mesh.indices[0].vertex_index * 3 + 2]);
		vec3 v1 = vec3(attrib.vertices[shapes[i].mesh.indices[1].vertex_index * 3 + 0],
					   attrib.vertices[shapes[i].mesh.indices[1].vertex_index * 3 + 1],
					   attrib.vertices[shapes[i].mesh.indices[1].vertex_index * 3 + 2]);
		vec3 v2 = vec3(attrib.vertices[shapes[i].mesh.indices[2].vertex_index * 3 + 0],
					   attrib.vertices[shapes[i].mesh.indices[2].vertex_index * 3 + 1],
					   attrib.vertices[shapes[i].mesh.indices[2].vertex_index * 3 + 2]);

		Triangle * triangle = new Triangle(v0, v1, v2);
		Shape * shape = triangle;
		Material* currMat = new Material(currBRDF);
		GeoPrimitive* geoPrim = new GeoPrimitive(shape, currMat, mat4(1.0));
		allPrims._primList.push_back(geoPrim);

	}

	cout << "Load file successful: " + filename + " " << boolalpha << ret << " \n";
}

void printRealVector(string name, vector<real_t> vert) {

	size_t vertSize = vert.size();
	float vertVal;

	cout << name + ": Size " << vertSize << "\n";
	for (int i = 0; i < vertSize; i++) {
		vertVal = vert[i];
		cout << vertVal << "\n";
	}

}