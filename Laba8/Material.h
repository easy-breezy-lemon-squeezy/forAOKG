#pragma once
#include <windows.h>
#include "glew-2.2.0/include/GL/glew.h"
#include <GL/gl.h>
#include "freeglut/include/GL/glut.h"
#include "freeglut/include/GL/freeglut.h"
// ����� ��� ������ � ����������
class PhongMaterial
{
public:
	// ����������� �� ���������
	PhongMaterial();
	// ������� ���������� ���������
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setEmission(float r, float g, float b, float a);
	void setShininess(float p);
	// �������� ���������� ��������� �� �������� ���������� �����
	//void load(std::string filename);
	// ��������� ���� ���������� ���������
	void apply();
	void load(const char* path);
private:
	// ������� ������������ 
	GLfloat ambient[4];
	// ��������� ������������
	GLfloat diffuse[4];
	// ���������� ������������
	GLfloat specular[4];
	// ������������
	GLfloat emission[4];
	// ������� ����������������
	GLfloat  shininess;
};