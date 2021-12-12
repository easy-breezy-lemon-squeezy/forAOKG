#pragma once
#include <windows.h>
#include "glew-2.2.0/include/GL/glew.h"
#include <GL/gl.h>
#include "freeglut/include/GL/glut.h"
#include "freeglut/include/GL/freeglut.h"
#include "Material.h"
#include "Mesh.h"
#include <memory>
using namespace std;
class GraphicObject
{
private:
	GLfloat angle;
	// Цвет модели
	GLfloat color[3];
	// Используемый материал
	shared_ptr<Material> material;
	shared_ptr<Mesh> mesh;

public:
	// Позиция и угол поворота для объекта
	GLfloat position[3];
	// Конструктор
	GraphicObject(void);
	// Задать позицию объекта
	void setPosition(float x, float y, float z);
	// Задать угол поворота в градусах относительно оси OY
	void setAngle(float a);
	// Задать цвет модели
	void setСolor(float r, float g, float b);
	// Вывести объект
	void draw(void);
	// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	GLfloat modelMatrix[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 0,0,0,1 };
	// Установка используемого материала
	void setMaterial(shared_ptr<Material> material2);
	void setMesh(shared_ptr<Mesh> mesh);
};