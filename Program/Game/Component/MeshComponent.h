#pragma once

#include "Component.h"

class Actor;
class Mesh;
class MeshComponent : public Component
{
public:
	MeshComponent(Actor* owner);
	virtual ~MeshComponent();

	virtual void Update() override;

	void SetMesh(Mesh* mesh) { mMesh = mesh; }

private:
	Mesh* mMesh;
};