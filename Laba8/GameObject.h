#pragma once
#include "glew-2.2.0/include/GL/glew.h"
#include "GraphObject.h"
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
using namespace std;

class GameObject
{
public:
	// �����������
	GameObject();
	// ��������� ������������� ������������ �������
	// ���������� ����������� ����������� ������� ��� ������������ �������������
	void setGraphicObject(shared_ptr<GraphicObject> graphcopy);
	// ��������� ���������� ��������� (��� ������������� ������ ��� ��������)
	void setPosition(float x, float y, float z);
	void setMesh(shared_ptr<Mesh> mesh);
	// ��������� ������� ���������� ���������
	//ivec2 getPosition();
	// ����� �������� ������� �� �����
	void draw(void);
private:
	// ���������� ���������� �������� �������
	float x, y;
	// ����������� ������ (��� ������ �� �����)
	shared_ptr<GraphicObject> graphic;
};