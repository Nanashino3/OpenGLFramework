#pragma once

#include "Renderer.h"
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(const char* shaderName = "Lambert");
	virtual ~MeshRenderer();

private:
	virtual void ActualDraw(void* drawObject) final;
	void SetLightUniforms();
};