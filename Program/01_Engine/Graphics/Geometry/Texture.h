//****************************************************************************
// ファイル名：Texture(テクスチャクラス)
// 作　成　日：2022/10/24
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../../../02_Library/Vector.h"

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
	void SetColor(const tkl::Vector3& color){ mColor = color; }
	const tkl::Vector3& GetColor() { return mColor; }

private:
	unsigned int mTextureID;
	int mTextureW;
	int mTextureH;
	tkl::Vector3 mColor;
};

} // namespace tkl

#endif