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
// класс-перечисление дл€ указани€ направлени€ перемещени€
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

class GameObject
{
public:
	// конструктор
	GameObject();
	// установка используемого графического объекта
	// происходит копирование переданного объекта дл€ последующего использовани€
	void setGraphicObject(shared_ptr<GraphicObject> graphcopy);
	// установка логических координат (два перегруженных метода дл€ удобства)
	void setPosition(float x, float y, float z);
	void setMesh(shared_ptr<Mesh> mesh);
	// получение текущих логических координат
	//ivec2 getPosition();
	// вывод игрового объекта на экран
	void draw(void);
	float getX();
	float getY();
	// начать движение в выбранном направлении с указанной скоростью 
	// скорость передвижени€ определ€етс€ количеством клеток в секунду
	void move(MoveDirection direction, float speed = 10.0f);
	// симул€ци€ игрового объекта (плавное перемещение объекта)
	// метод вызываетс€ непрерывно в функции simulation
	void simulate(float sec);
	// проверка на то, что объект в насто€щий момент движетс€
	bool isMoving();
	void setExist(bool value);
	bool getExist();
private:
	// логические координаты игрового объекта
	float x, y;
	// графический объект (дл€ вывода на экран)
	shared_ptr<GraphicObject> graphic;
	// состо€ние объекта (заданное направление перемещени€)
	MoveDirection state;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress=0.0f;
	// скорость перемещени€
	float speed;
	bool exist = true;
};
class Monster : public GameObject
{
public:
	Monster();
	// установить прошлые координаты
	void setLastStand(int x, int y);
	// получить прошлые координаты
	int getLastStandX();
	int getLastStandY();
	// перемещение монстров
	void monsterSimulation();

private:
	// прошлые координаты дл€ монстра
	int lastX, lastY;
};