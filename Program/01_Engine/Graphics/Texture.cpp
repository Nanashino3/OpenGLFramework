#include "Texture.h"
#include <GL/glew.h>

namespace tkl
{
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

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

} // namespace tkl