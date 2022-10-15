#pragma once

#include "Renderer.h"
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(Mesh* mesh, const char* shaderName);
	virtual ~MeshRenderer();

	virtual void Draw(Camera* camera);

private:
	void SetLightUniforms();
};