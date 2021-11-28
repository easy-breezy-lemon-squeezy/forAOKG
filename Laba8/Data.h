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

LARGE_INTEGER OldSimTik, NewSimTik, frequency;

/*int passabilityMap[21][21] = {
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
};*/

Camera camera;
Light light;
#define SIZE 21

// задание всех параметров одного материала
PhongMaterial material1, material2, material3, material4;
shared_ptr<GameObject> mapObjects[SIZE][SIZE];


shared_ptr<GameObject> player;
GraphicObject planeGraphicObject;

vector<shared_ptr<PhongMaterial>> materials;
vector<shared_ptr<Mesh>> mesh;

GraphicObject graph1, graph2, graph3, graph0;

GLfloat globalAmbientColor[] = { 0.8, 0.8, 0.8, 1.0 };

shared_ptr<vector<vector<char>>> Array = MazeGenerator::generate(SIZE/2, SIZE/2);

// фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{
	// инициализация фабрики (в дальнейшем на основе json-файла)
	gameObjectFactory.init("data//GameObjectsDescription.json");
	// инициализация объектов сцены
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
	
			if ((Array.get()->at(i).at(j)) == '3') {
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, 0, j);
			}
			else if((Array.get()->at(i).at(j)) == '2') {
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