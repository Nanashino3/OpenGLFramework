#pragma once

#include "Renderer.h"
class WireRenderer : public Renderer
{
public:
	WireRenderer(Mesh* mesh, const char* shaderName);
	virtual ~WireRenderer();

private:
	virtual void ActualDraw(Mesh* mesh) final;
};