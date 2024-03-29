#pragma once
#include "glew-2.2.0/include/GL/glew.h"
#include "GraphObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "MazeGenerator.h"
#include "Simulation.h"
#include "Texture.h"

LARGE_INTEGER OldSimTik, NewSimTik, frequency;


Camera camera;
Light light;
#define SIZE 21

// ������� ���� ���������� ������ ���������
PhongMaterial material1, material2, material3, material4;
shared_ptr<GameObject> mapObjects[SIZE][SIZE];
shared_ptr<GameObject> player;
bool showPlayer;
shared_ptr <Monster> enemy[3];
GraphicObject planeGraphicObject;

vector<shared_ptr<PhongMaterial>> materials;
vector<shared_ptr<Mesh>> mesh;
Texture planeTexture;

GraphicObject graph1, graph2, graph3, graph0;

GLfloat globalAmbientColor[] = { 0.8, 0.8, 0.8, 1.0 };

shared_ptr<vector<vector<char>>> Array = MazeGenerator::generate(SIZE / 2, SIZE / 2);

// ������� ��� �������� ������� ��������
GameObjectFactory gameObjectFactory;
// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData()
{
	// ������������� ������� (� ���������� �� ������ json-�����)
	gameObjectFactory.init();

	planeTexture.load("data\\textures\\plane.jpg");
	showPlayer = true;
	// ������������� �������� �����
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			if ((Array.get()->at(i).at(j)) == '3') {
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, 0, j);
			}
			else if ((Array.get()->at(i).at(j)) == '2') {
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, 0, j);

			}
			else if ((Array.get()->at(i).at(j)) == '1') {
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, 0, j);
			}
			else if ((Array.get()->at(i).at(j)) == '0') {
				mapObjects[i][j] = nullptr;

			}

		}

	}

	// ������������� �������� �����
	player = gameObjectFactory.create(GameObjectType::PLAYER, 19, 0, 1);
	//�������
	enemy[0] = gameObjectFactory.create(GameObjectType::MONSTER, 19, 0, 19, 1);
	enemy[1] = gameObjectFactory.create(GameObjectType::MONSTER, 1, 0, 19, 1);
	enemy[2] = gameObjectFactory.create(GameObjectType::MONSTER, 1, 0, 1, 1);

	enemy[0].get()->setLastStand(19, 19);
	enemy[1].get()->setLastStand(1, 19);
	enemy[2].get()->setLastStand(1, 1);

	// ������������� ���������
	planeGraphicObject.setPosition(0, -0.5, 0);
	shared_ptr<Mesh> planeMesh = make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);
	shared_ptr<PhongMaterial> planeMaterial = make_shared<PhongMaterial>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeGraphicObject.setMaterial(planeMaterial);
}

void initGlew() {
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	if (GLEW_ARB_vertex_buffer_object) {
		printf("VBO is supported");
	};
}