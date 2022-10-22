#pragma once

#include "Renderer.h"
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(Mesh* mesh, const char* shaderName);
	virtual ~MeshRenderer();

private:
	virtual void ActualDraw(Mesh* mesh) final;
	void SetLightUniforms();
};