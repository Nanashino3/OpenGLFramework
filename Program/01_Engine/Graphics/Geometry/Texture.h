//****************************************************************************
// ファイル名：Texture(テクスチャクラス)
// 作　成　日：2022/10/24
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <ft2build.h>
#include FT_FREETYPE_H

namespace tkl
{
class Texture
{
public:
	Texture();
	~Texture();

	void Bind();
	void CreateBuffer(int width, int height, void* pixels, int channels = 4);
	void CreateBufferFromTTF(const FT_Bitmap& bitmap);

	int GetWidth() const { return mTextureW; }
	int GetHeight() const { return mTextureH; }
	unsigned int GetTextureID() const { return mTextureID; }
private:
	unsigned int mTextureID;
	int mTextureW;
	int mTextureH;
};

} // namespace tkl

#endif