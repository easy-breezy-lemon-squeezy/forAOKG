#pragma once
#include "GraphObject.h"
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
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

// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ
enum class GameObjectType {
	LIGHT_OBJECT, // легкий игровой объект
	HEAVY_OBJECT, // тяжелый игровой объект
	BORDER_OBJECT, // граничный игровой объект
	PLAYER, // игровой объект для представления игрока
	BOMB, // игровой объект для представления бомбы
	MONSTER // игровой объект для представления монстров
};

/*string type[] = { "LightObject", "HeavyObject", "BorderObject", "Player", "Bomb", "Monster" };
int typeSize = 6;*/
class GameObjectFactory
{
public:
	// инициализация фабрики (загрузка мешей и установка параметров материала)
	bool init();
	// создание нового объекта заданного типа
	shared_ptr<GameObject> create(GameObjectType type, int x, int y, int z);
	shared_ptr<Monster> create(GameObjectType type, int x, int y, int z, bool monster);
private:
	// меши для каждого типа объекта
	vector<shared_ptr<Mesh>> meshes;
	// материалы для каждого типа объекта
	vector<shared_ptr<PhongMaterial>> materials;
};