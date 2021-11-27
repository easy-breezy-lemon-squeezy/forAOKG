#pragma once
#include "GraphObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

LARGE_INTEGER OldSimTik, NewSimTik, frequency;

int passabilityMap[21][21] = {
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

Camera camera;
Light light;
// задание всех параметров одного материала
PhongMaterial material1, material2, material3, material4;
shared_ptr<GameObject> mapObjects[21][21];
shared_ptr<GameObject> player;
GraphicObject planeGraphicObject;

vector<shared_ptr<PhongMaterial>> materials;
vector<shared_ptr<Mesh>> mesh;

GraphicObject graph1, graph2, graph3, graph0;

GLfloat globalAmbientColor[] = { 0.8, 0.8, 0.8, 1.0 };

// фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{
	// инициализация фабрики (в дальнейшем на основе json-файла)
	gameObjectFactory.init("data//GameObjectsDescription.json");
	// инициализация объектов сцены
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, 0, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, 0, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, 0, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}
	// инициализация главного героя
	player = gameObjectFactory.create(GameObjectType::PLAYER, 19, 0, 1);
	// инициализация плоскости
	planeGraphicObject.setPosition(0, -0.5, 0);
	shared_ptr<Mesh> planeMesh = make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);
	shared_ptr<PhongMaterial> planeMaterial = make_shared<PhongMaterial>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeGraphicObject.setMaterial(planeMaterial);
}
