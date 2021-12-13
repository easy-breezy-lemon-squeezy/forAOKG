#pragma once
#include "GraphObject.h"
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include <GL/gl.h>
#include "freeglut/include/GL/glut.h"
#include "freeglut/include/GL/freeglut.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <memory>

using namespace std;

// ����������� ����� ������� ��������
enum class GameObjectType {
	LIGHT_OBJECT, // ������ ������� ������
	HEAVY_OBJECT, // ������� ������� ������
	BORDER_OBJECT, // ��������� ������� ������
	PLAYER, // ������� ������ ��� ������������� ������
	BOMB, // ������� ������ ��� ������������� �����
	MONSTER // ������� ������ ��� ������������� ��������
};

class GameObjectFactory
{
public:
	// ������������� ������� (�������� ����� � ��������� ���������� ���������)
	bool init();
	// �������� ������ ������� ��������� ����
	shared_ptr<GameObject> create(GameObjectType type, int x, int y, int z);
	shared_ptr<Monster> create(GameObjectType type, int x, int y, int z, bool monster);
private:
	// ���� ��� ������� ���� �������
	vector<shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	vector<shared_ptr<PhongMaterial>> materials;
	vector <shared_ptr<PhongMaterialWithTexture>> materialsWithTexture;
	// ��������
	vector<shared_ptr <Texture>> textures;
};