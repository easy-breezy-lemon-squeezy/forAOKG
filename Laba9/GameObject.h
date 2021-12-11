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
using namespace std;

// класс-перечисление для указания направления перемещения
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

class GameObject
{
public:
	// конструктор
	GameObject();
	// установка используемого графического объекта
	// происходит копирование переданного объекта для последующего использования
	void setGraphicObject(shared_ptr<GraphicObject> graphcopy);
	// установка логических координат (два перегруженных метода для удобства)
	void setPosition(float x, float y, float z);
	void setMesh(shared_ptr<Mesh> mesh);
	// получение текущих логических координат
	//ivec2 getPosition();
	// вывод игрового объекта на экран
	void draw(void);
	float getX();
	float getY();
	// начать движение в выбранном направлении с указанной скоростью 
	// скорость передвижения определяется количеством клеток в секунду
	void move(MoveDirection direction, float speed = 10.0f);

	// симуляция игрового объекта (плавное перемещение объекта)
	// метод вызывается непрерывно в функции simulation
	void simulate(float sec);

	// проверка на то, что объект в настоящий момент движется
	bool isMoving();
private:
	// логические координаты игрового объекта
	float x, y;
	// графический объект (для вывода на экран)
	shared_ptr<GraphicObject> graphic;
	// состояние объекта (заданное направление перемещения)
	MoveDirection state;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress=0.0f;
	// скорость перемещения
	float speed;
};