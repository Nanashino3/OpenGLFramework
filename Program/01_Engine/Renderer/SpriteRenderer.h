//****************************************************************************
// �t�@�C�����FSpriteRenderer(�X�v���C�g�����_���[�N���X)
// ��@���@���F2022/10/26
#ifndef _SPRITERENDERER_H_
#define _SPRITERENDERER_H_

#include "Renderer.h"
namespace tkl
{
class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer(const char* shaderName = "Sprite");
	virtual ~SpriteRenderer();

	virtual void Draw(std::shared_ptr<Mesh> mesh) final;
};

} // namespace tkl

#endif