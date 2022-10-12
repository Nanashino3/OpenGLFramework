#pragma once

#include "Renderer.h"
class WireRenderer : public Renderer
{
public:
	WireRenderer(Mesh* mesh);
	virtual ~WireRenderer();

	virtual void Draw(Camera* camera);
};