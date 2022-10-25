#include "Texture.h"
#include <GL/glew.h>
#include <SOIL.h>

Texture::Texture(int width, int height, void* pixels, int channels)
{
	mTextureW = width;
	mTextureH = height;

	int format = (channels == 4) ? GL_RGBA : GL_RGB;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mTextureW, mTextureH, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{}

// ファイル名によるテクスチャ生成
Texture* Texture::CreateTextureFromFile(const char* fileName)
{
	int channels = 0, textureW = 0, textureH = 0;
	unsigned char* image = SOIL_load_image(fileName, &textureW, &textureH, &channels, SOIL_LOAD_AUTO);
	if(image == nullptr){ return nullptr; }

	Texture* newTexture = new Texture(textureW, textureH, image, channels);
	return newTexture;
}

void Texture::Bind()
{
//	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}