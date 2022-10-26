#pragma once

#include "Renderer.h"
class WireRenderer : public Renderer
{
public:
	WireRenderer(const char* shaderName = "Basic");
	virtual ~WireRenderer();

private:
	virtual void ActualDraw(void* drawObject) final;
};