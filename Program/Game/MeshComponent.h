#pragma once

#include "Component.h"
class Mesh;
class Shader;
class MeshComponent : public Component
{
public:
	MeshComponent();
	virtual ~MeshComponent();

	void Draw(Shader* shader);
	void SetMesh(Mesh* mesh){ mMesh = mesh; }
private:
	Mesh* mMesh;
};