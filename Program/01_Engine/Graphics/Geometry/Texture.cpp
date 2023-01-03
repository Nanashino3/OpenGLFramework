//****************************************************************************
// ファイル名：Texture(テクスチャクラス)
// 作　成　日：2022/10/24
#include "Texture.h"
#include <GL/glew.h>

namespace tkl
{
Texture::Texture()
: mTextureID(0)
, mTextureW(0), mTextureH(0)
{}

Texture::~Texture()
{}

//****************************************************************************
// 関数名：CreateBuffer
// 概　要：バッファの作成
// 引　数：arg1 テクスチャの幅
//       ：arg2 テクスチャの高さ
//       ：arg3 カラー配列
//       ：arg4 チャネル数
// 戻り値：なし
// 詳　細：GPU側に必要な情報を覚えさせる
//****************************************************************************
void Texture::CreateBuffer(int width, int height, void* pixels, int channels)
{
	mTextureW = width;
	mTextureH = height;

	int format = (channels == 4) ? GL_RGBA : GL_RGB;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mTextureW, mTextureH, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//****************************************************************************
// 関数名：CreateBufferFromTTF
// 概　要：バッファの作成(TTF)
// 引　数：arg1 ビットマップ情報(freetype)
// 戻り値：なし
// 詳　細：GPU側に必要な情報を覚えさせる
//****************************************************************************
void Texture::CreateBufferFromTTF(const FT_Bitmap& bitmap)
{
	mTextureW = bitmap.width;
	mTextureH = bitmap.rows;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, mTextureW, mTextureH, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//****************************************************************************
// 関数名：Bind
// 概　要：バインド
// 引　数：なし
// 戻り値：なし
// 詳　細：テクスチャを有効化する
//****************************************************************************
void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

} // namespace tkl