#pragma once
#include "glew-2.2.0/include/GL/glew.h"
#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include "freeglut/include/GL/glut.h"
#include "freeglut/include/GL/freeglut.h"

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
	void load(string filename);
	void draw();
private:
	int indexCount;
	GLuint bufferIds[2];
};