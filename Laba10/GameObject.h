#pragma once
#include "GraphObject.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include "freeglut/include/GL/glut.h"
#include "freeglut/include/GL/freeglut.h"
#include <time.h>

using namespace std;
extern shared_ptr<vector<vector<char>>> Array;
// �����-������������ ��� �������� ����������� �����������
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
	void setMesh(shared_ptr<Mesh> mesh);
	// ��������� ������� ���������� ���������
	//ivec2 getPosition();
	// ����� �������� ������� �� �����
	void draw(void);
	float getX();
	float getY();
	// ������ �������� � ��������� ����������� � ��������� ��������� 
	// �������� ������������ ������������ ����������� ������ � �������
	void move(MoveDirection direction, float speed = 10.0f);
	// ��������� �������� ������� (������� ����������� �������)
	// ����� ���������� ���������� � ������� simulation
	void simulate(float sec);
	// �������� �� ��, ��� ������ � ��������� ������ ��������
	bool isMoving();
	void setExist(bool value);
	bool getExist();
private:
	// ���������� ���������� �������� �������
	float x, y;
	// ����������� ������ (��� ������ �� �����)
	shared_ptr<GraphicObject> graphic;
	// ��������� ������� (�������� ����������� �����������)
	MoveDirection state;
	// �������� � ����������� (�� 0.0 �� 1.0)
	float progress=0.0f;
	// �������� �����������
	float speed;
	bool exist = true;
};
class Monster : public GameObject
{
public:
	Monster();
	// ���������� ������� ����������
	void setLastStand(int x, int y);
	// �������� ������� ����������
	int getLastStandX();
	int getLastStandY();
	// ����������� ��������
	void monsterSimulation();

private:
	// ������� ���������� ��� �������
	int lastX, lastY;
};