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

	static Texture* CreateTextureFromFile(const char* fileName);

	tkl::Vector3 mPosition;
private:
	unsigned int mTextureID;
	int mTextureW;
	int mTextureH;
};