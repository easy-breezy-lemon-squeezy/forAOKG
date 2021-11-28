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
private:
	// логические координаты игрового объекта
	float x, y;
	// графический объект (для вывода на экран)
	shared_ptr<GraphicObject> graphic;
};