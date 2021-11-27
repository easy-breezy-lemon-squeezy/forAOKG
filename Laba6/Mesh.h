#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"

using namespace std;

struct Vertex {
	GLfloat coord[3];
	GLfloat normal[3];
	GLfloat texCoord[2];
};


struct cord {
	float x = 0;
	float y = 0;
	float z = 0;
};

struct cord1 {
	float s = 0;
	float t = 0;
};

class Mesh {
public:
	Mesh();
	void load(const char* file);
	void draw();
private:
	vector<Vertex> vertices;
};