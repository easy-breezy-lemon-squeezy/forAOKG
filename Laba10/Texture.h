#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>
#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include <IL\il.h>

// ѕ≈–≈„»—Ћ≈Ќ»≈ ƒЋя ќѕ–≈ƒ≈Ћ≈Ќ»я –≈∆»ћј ‘»Ћ№“–ј÷»»
enum class TextureFilter
{
	POINT, // “ќ„≈„Ќјя
	BILINEAR, // Ѕ»Ћ»Ќ≈…Ќјя
	TRILINEAR, // “–»Ћ»Ќ≈…Ќјя
	ANISOTROPIC // јЌ»«“ќ–ќѕЌјя
};


class Texture
{
public:
	// загрузка текстуры из внешнего файла
	void load(std::string filename);

	// применение текстуры (прив¤зка к текстурному блоку и установка параметров)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);

	// отключение текстурировани¤ дл¤ всех текстурных блоков
	static void disableAll();

private:
	// идентификатор (индекс) текстурного объекта
	GLuint texIndex;
};

