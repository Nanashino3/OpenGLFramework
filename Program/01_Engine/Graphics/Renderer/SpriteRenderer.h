//****************************************************************************
// ファイル名：SpriteRenderer(スプライトレンダラークラス)
// 作　成　日：2022/10/26
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