#pragma once

#include "Renderer.h"
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(const char* shaderName = "Lambert");
	virtual ~MeshRenderer();

private:
	virtual void ActualDraw(std::shared_ptr<Mesh> mesh) final;
	void SetLightUniforms();
};