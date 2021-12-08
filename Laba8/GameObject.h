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
// класс-перечисление дл¤ указани¤ направлени¤ перемещения
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
	float* getPosition();
	void setMesh(shared_ptr<Mesh> mesh);
	// получение текущих логических координат
	// вывод игрового объекта на экран
	void draw(void);
	void move(MoveDirection direction, float speed = 3.0f);
	// метод вызываетс¤ непрерывно в функции simulation
	void simulate(float sec);
	// проверка на то, что объект в настощий момент движетс¤
	bool isMoving();
private:
	// логические координаты игрового объекта
	float x, y;
	float time;
	// графический объект (для вывода на экран)
	shared_ptr<GraphicObject> graphic;
	// состояние объекта (заданное направление перемещения)
	MoveDirection state = MoveDirection::STOP;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress;
	// скорость перемещения
	float speed;
};