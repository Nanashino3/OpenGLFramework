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