#include "pch.h"
#include "Loader.h"

void readfile(string filename, string mtlPath, AllPrimitives& allPrims)
{
	tinyobj::attrib_t attrib;
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;

	string warn;
	string err;

	int numTriangles = 0;
	vec3 v0, v1, v2, vn0, vn1, vn2;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), mtlPath.c_str());

	//printRealVector("vertices",  attrib.vertices);
	//printRealVector("normals",   attrib.normals);
	//printRealVector("texcoords", attrib.texcoords);
	//printRealVector("colors",    attrib.colors);

	//cout << "Mat Size: " << materials.size() << "\n";

	for (size_t i = 0; i < shapes.size(); i++) {
		//cout << shapes[i].name + "\n";
		//cout << "Vertex Ind: \n";
		//for (int j = 0; j < shapes[i].mesh.indices.size(); j++) {
		//	cout << shapes[i].mesh.indices[j].vertex_index << "\n";
		//}

		numTriangles = ((int) shapes[i].mesh.indices.size()) / 3;
		for (size_t j = 0; j < numTriangles; j++) {
			BRDF currBRDF = BRDF();
			material_t mat = materials[shapes[i].mesh.material_ids[j]];
			vec3 ambient = vec3(0, 0, 0);
			// vec3 ambient = vec3(mat.ambient[0], mat.ambient[1], mat.ambient[2]);
			vec3 diffuse = vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
			vec3 specular = vec3(mat.specular[0], mat.specular[1], mat.specular[2]);
			//g_printer->printVec("ambient", ambient);
			//g_printer->printVec("diffuse", diffuse);
			//g_printer->printVec("specular", specular);

			currBRDF = BRDF(ambient, mat.shininess, diffuse, specular, currBRDF._ke);

			v0 = vec3(attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 0].vertex_index) * 3 + 0],
				      attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 0].vertex_index) * 3 + 1],
				      attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 0].vertex_index) * 3 + 2]);
			v1 = vec3(attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 1].vertex_index) * 3 + 0],
				      attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 1].vertex_index) * 3 + 1],
				      attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 1].vertex_index) * 3 + 2]);
			v2 = vec3(attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 2].vertex_index) * 3 + 0],
				      attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 2].vertex_index) * 3 + 1],
				      attrib.vertices[((size_t)shapes[i].mesh.indices[j*3 + 2].vertex_index) * 3 + 2]);

			vn0 = vec3(attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 0].normal_index) * 3 + 0],
				       attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 0].normal_index) * 3 + 1],
				       attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 0].normal_index) * 3 + 2]);
			vn1 = vec3(attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 1].normal_index) * 3 + 0],
				       attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 1].normal_index) * 3 + 1],
				       attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 1].normal_index) * 3 + 2]);
			vn2 = vec3(attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 2].normal_index) * 3 + 0],
				       attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 2].normal_index) * 3 + 1],
				       attrib.normals[((size_t)shapes[i].mesh.indices[j*3 + 2].normal_index) * 3 + 2]);

			Triangle * triangle = new Triangle(v0, v1, v2, vn0, vn1, vn2);
			Shape * shape = triangle;
			Material * currMat = new Material(currBRDF);
			GeoPrimitive * geoPrim = new GeoPrimitive(shape, currMat, mat4(1.0));
			allPrims._primList.push_back(geoPrim);
		}

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