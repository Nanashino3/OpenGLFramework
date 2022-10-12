#pragma once

#include "Component.h"
class Mesh;
class Shader;
class WireComponent : public Component
{
public:
	WireComponent();
	virtual ~WireComponent();

	void Draw(Shader* shader);
	void SetMesh(Mesh* mesh) { mMesh = mesh; }
private:
	Mesh* mMesh;
};