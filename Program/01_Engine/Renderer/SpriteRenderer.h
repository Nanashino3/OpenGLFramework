#pragma once

#include "Renderer.h"
class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer(const char* shaderName = "Sprite");
	virtual ~SpriteRenderer();

private:
	virtual void ActualDraw(void* drawObject) final;
};