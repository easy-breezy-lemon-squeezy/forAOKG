#include "Mesh.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <iterator>
using namespace std;

Mesh::Mesh(void) {}

void Mesh::load(string filename) {
	vector<Vertex> vertices;  //массив вершин
	vector<GLuint> indices;   //массив индексов
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
			auto fi = vertexToIndexTable.find(index);    // получаем элемент с ключом index
			if (fi == vertexToIndexTable.end()) {        // если вершина не найдена то   
				vertexToIndexTable.insert(pair<string, int>(index, m));     // вставляем ее в таблицу вершина и ее индекс
				indices.push_back(m);   //вставляем индекс в массив индексов
				++m;                    
				faces.push_back(face);  //первую часть треугольничка полигона  
			}
			else {
				indices.push_back(fi->second);   //  вставляем индекс в массив индексов 
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
		// Структура, описывающая одну вершину полигональной сетки
		// каждая вершина имеет геометрические координаты,
		// вектор нормали и текстурные координаты
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
	//VBO
	//удаляем старые буферы, если они есть
	if (bufferIds[0] != 0) {
		glDeleteBuffers(1, &bufferIds[0]);
	}
	if (bufferIds[1] != 0) {
		glDeleteBuffers(1, &bufferIds[1]);
	}
	//создаем новые буферы
	glGenBuffers(2, bufferIds);
	//заполняем буфер вершин
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//заполняем буфер индексов
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//определяем количество вершин (индексов)
	indexCount = indices.size();
}

void Mesh::draw() {
	if (indexCount == 0) return;

	//включаем вершинные массивы
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	//указываем откуда и как брать атрибуты вершин
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, coord));

	//выводим модель
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	//отвязываем буферы и отключаем ненужные массивы
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}