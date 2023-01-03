//****************************************************************************
// �t�@�C�����FTexture(�e�N�X�`���N���X)
// ��@���@���F2022/10/24
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
// �֐����FCreateBuffer
// �T�@�v�F�o�b�t�@�̍쐬
// ���@���Farg1 �e�N�X�`���̕�
//       �Farg2 �e�N�X�`���̍���
//       �Farg3 �J���[�z��
//       �Farg4 �`���l����
// �߂�l�F�Ȃ�
// �ځ@�ׁFGPU���ɕK�v�ȏ����o��������
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
// �֐����FCreateBufferFromTTF
// �T�@�v�F�o�b�t�@�̍쐬(TTF)
// ���@���Farg1 �r�b�g�}�b�v���(freetype)
// �߂�l�F�Ȃ�
// �ځ@�ׁFGPU���ɕK�v�ȏ����o��������
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
// �֐����FBind
// �T�@�v�F�o�C���h
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N�X�`����L��������
//****************************************************************************
void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

} // namespace tkl