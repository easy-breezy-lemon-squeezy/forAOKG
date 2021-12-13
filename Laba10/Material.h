
#pragma once
#include <windows.h>
#include "glew-2.2.0/include/GL/glew.h"
#include <GL/gl.h>
#include "freeglut/include/GL/glut.h"
#include "freeglut/include/GL/freeglut.h"
#include "Texture.h"
#include <memory>
using namespace std;
// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class Material
{
public:
	virtual void apply(void) = 0;
};
class PhongMaterial : public Material
{
public:
	// конструктор по умолчанию
	PhongMaterial();
	// задание параметров материала
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setEmission(float r, float g, float b, float a);
	void setShininess(float p);
	// загрузка параметров материала из внешнего текстового файла
	//void load(std::string filename);
	// установка всех параметров материала
	void apply();
	void load(const char* path);
private:
	// фоновая составляющая 
	GLfloat ambient[4];
	// диффузная составляющая
	GLfloat diffuse[4];
	// зеркальная составляющая
	GLfloat specular[4];
	// самосвечение
	GLfloat emission[4];
	// степень отполированности
	GLfloat  shininess;
};
class PhongMaterialWithTexture : public Material
{
public:
	// конструктор по умолчанию
	PhongMaterialWithTexture();
	// задание параметров материала
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setEmission(float r, float g, float b, float a);
	void setShininess(float p);
	// загрузка параметров материала из внешнего текстового файла
	// установка всех параметров материала
	void apply();
	void load(const char* path);
	// установка используемой текстуры
	void setTexture(shared_ptr<Texture> texture);
private:
	// фоновая составляющая 
	GLfloat ambient[4];
	// диффузная составляющая
	GLfloat diffuse[4];
	// зеркальная составляющая
	GLfloat specular[4];
	// самосвечение
	GLfloat emission[4];
	// степень отполированности
	GLfloat  shininess;
	// используемая текстура
	shared_ptr<Texture> texture;
};