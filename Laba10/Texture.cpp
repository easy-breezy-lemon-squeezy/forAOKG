#include "Texture.h"
#include <IL\il.h>
#include <iostream>
using namespace std;

void Texture::load(std::string filename)
{
	// определ€ем модель пам€ти (параметры распаковки)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// создаем новое "изображение"
	ILuint imageId = ilGenImage();
	// задаем текущее "изображение"
	ilBindImage(imageId);
	// загружаем изображение
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());
	bool result = ilLoadImage(unicodeString);
	
	//grab data and release the IL image
	int w = ilGetInteger(IL_IMAGE_WIDTH);
	int h = ilGetInteger(IL_IMAGE_HEIGHT);
	char* data = new char[w * h * 4];
	ilCopyPixels(0, 0, 0, w, h, 1, IL_RGBA, IL_UNSIGNED_BYTE, data);
	

	// генерируем текстурный объект
	glGenTextures(1, &this->texIndex);

	// делаем текстурный объект текущим
	glBindTexture(GL_TEXTURE_2D, this->texIndex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// отв€зывем текущую текстуру
	glBindTexture(GL_TEXTURE_2D, 0);

	//free all the temp data
	delete[] data;
}

void Texture::apply(TextureFilter texFilter)
{
	

	glBindTexture(GL_TEXTURE_2D, this->texIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	switch (texFilter)
	{
	case TextureFilter::POINT:
		break;
	case TextureFilter::BILINEAR:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter::TRILINEAR:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter::ANISOTROPIC:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
}

void Texture::disableAll()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
