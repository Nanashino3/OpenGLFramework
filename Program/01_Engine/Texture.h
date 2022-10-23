#pragma once

class Texture
{
public:
	Texture(int width, int height, void* pixels);
	~Texture();

	void Bind();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	unsigned int GetTextureID() const { return mTextureID; }

private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};