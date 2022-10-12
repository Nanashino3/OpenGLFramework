#pragma once

#include "Renderer.h"

class Mesh;
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(Mesh* mesh);
	virtual ~MeshRenderer();

	virtual void Draw(Camera* camera);

private:
	void SetLightUniforms();
};