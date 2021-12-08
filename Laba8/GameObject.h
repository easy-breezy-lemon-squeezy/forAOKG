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
// �����-������������ �� ������� ���������� �����������
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };
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
	float* getPosition();
	void setMesh(shared_ptr<Mesh> mesh);
	// ��������� ������� ���������� ���������
	// ����� �������� ������� �� �����
	void draw(void);
	void move(MoveDirection direction, float speed = 3.0f);
	// ����� ��������� ���������� � ������� simulation
	void simulate(float sec);
	// �������� �� ��, ��� ������ � �������� ������ �������
	bool isMoving();
private:
	// ���������� ���������� �������� �������
	float x, y;
	float time;
	// ����������� ������ (��� ������ �� �����)
	shared_ptr<GraphicObject> graphic;
	// ��������� ������� (�������� ����������� �����������)
	MoveDirection state = MoveDirection::STOP;
	// �������� � ����������� (�� 0.0 �� 1.0)
	float progress;
	// �������� �����������
	float speed;
};