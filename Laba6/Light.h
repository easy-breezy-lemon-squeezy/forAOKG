#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
// ����� ��� ������ � ���������� �����
class Light
{
public:
	// ������������
	Light();
	//Light(float x, float y, float z);
	Light(float x, float y, float z);
	// ������� ��������� ���������� ��������� �����
	void setPosition(int x, int y, int z);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	// ��������� ���� ���������� ��������� ����� � �������� �������
	// ������ ������� ������ ���������� ����� ��������� ������,
	// �.�. ����� ��������������� ������� ��������� �����
	void apply();
private:
	// ������� ��������� �����
	GLfloat position[3];
	// ������� ������������ ��������� �����
	GLfloat ambient[4];
	// ��������� ������������
	GLfloat diffuse[4];
	// ���������� ������������
	GLfloat specular[4];
};