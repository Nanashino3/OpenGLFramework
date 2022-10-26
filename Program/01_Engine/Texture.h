#pragma once
#include "../02_Library/Vector.h"

class Texture
{
public:
	Texture(int width, int height, void* pixels, int channels = 4);
	~Texture();

	void Bind();

	int GetTextureWidth() const { return mTextureW; }
	int GetTextureHeight() const { return mTextureH; }
	unsigned int GetTextureID() const { return mTextureID; }
private:
	unsigned int mTextureID;
	int mTextureW;
	int mTextureH;
};