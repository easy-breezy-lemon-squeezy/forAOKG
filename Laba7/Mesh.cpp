#include "Mesh.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <iterator>
using namespace std;

Mesh::Mesh(void) {}

void Mesh::load(string filename) {

	int m = 0;
	map<string, int> vertexToIndexTable;
	
	ofstream fout;
	ifstream f;
	f.open(filename);
	if (!f.is_open()) {
		printf("Can not open file %s\n", filename.c_str());
		return;
	}
	string s;
	char temp[512];
	vector<cord> v;
	vector<cord> n;
	vector<cord1> t;
	vector<cord> faces;

	while (!f.eof()) {
		f >> s;
		if (s == "v") {
			cord vTemp;
			f >> vTemp.x >> vTemp.y >> vTemp.z;
			v.push_back(vTemp);
		}
		if (s == "vn") {
			cord vTemp;
			f >> vTemp.x >> vTemp.y >> vTemp.z;
			n.push_back(vTemp);
		}
		if (s == "vt") {
			cord1 vTemp;
			f >> vTemp.s >> vTemp.t;
			t.push_back(vTemp);
		}
		if (s == "f") {
			cord face;
			string index;
			char ch;
			f >> face.x >> ch >> face.y >> ch >> face.z;
			index = to_string(int(face.x * 100 + face.y * 10 + face.z));
			auto fi = vertexToIndexTable.find(index);
			if (fi == vertexToIndexTable.end()) {
				vertexToIndexTable.insert(pair<string, int>(index, m));
				indices.push_back(m);
				++m;
				faces.push_back(face);
			}
			else {
				indices.push_back(fi->second);
			}
			f >> face.x >> ch >> face.y >> ch >> face.z;
			index = to_string(int(face.x * 100 + face.y * 10 + face.z));
			auto fi1 = vertexToIndexTable.find(index);
			if (fi1 == vertexToIndexTable.end()) {
				vertexToIndexTable.insert(pair<string, int>(index, m));
				indices.push_back(m);
				++m;
				faces.push_back(face);
			}
			else {
				indices.push_back(fi1->second);
			}
			f >> face.x >> ch >> face.y >> ch >> face.z;
			index = to_string(int(face.x * 100 + face.y * 10 + face.z));
			auto fi2 = vertexToIndexTable.find(index);
			if (fi2 == vertexToIndexTable.end()) {
				vertexToIndexTable.insert(pair<string, int>(index, m));
				indices.push_back(m);
				++m;
				faces.push_back(face);
			}
			else {
				indices.push_back(fi2->second);
			}
		}
		f.getline(temp, 512);
	}
	f.close();
	vertices.clear();
	for (int i = 0; i < faces.size(); i++) {
		Vertex vtx;
		vtx.coord[0] = v[faces[i].x - 1].x;
		vtx.coord[1] = v[faces[i].x - 1].y;
		vtx.coord[2] = v[faces[i].x - 1].z;
		vtx.texCoord[0] = t[faces[i].y - 1].s;
		vtx.texCoord[1] = t[faces[i].y - 1].t;
		vtx.normal[0] = n[faces[i].z - 1].x;
		vtx.normal[1] = n[faces[i].z - 1].y;
		vtx.normal[2] = n[faces[i].z - 1].z;
		vertices.push_back(vtx);
	}
}

void Mesh::draw() {
	if (vertices.size() == 0) return;

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), vertices[0].texCoord);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), vertices[0].normal);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), vertices[0].coord);

	GLuint* pointer1 = &indices[0];
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, pointer1);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}