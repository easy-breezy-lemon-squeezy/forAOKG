#pragma once

#include <Windows.h>
#include <stdio.h>

#include "GameObject.h"
#include "Mesh.h"
#include "GraphObject.h"
#include "Material.h"

#include <memory>
#include <vector>
#include <fstream>

#include "rapidjson/document.h"

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

enum class GameObjectType
{
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
	bool init(std::string filename);
	shared_ptr<GameObject> create(GameObjectType type, int x, int y, int z);
	shared_ptr<Monster> create(GameObjectType type, int x, int y, int z, bool monster);

private:
	vector<shared_ptr<Mesh>> meshes;
	vector<shared_ptr<PhongMaterial>> materials;
	vector<shared_ptr<PhongMaterialWithTexture>> materialsWithTexture;
	vector<shared_ptr <Texture>> textures;
};