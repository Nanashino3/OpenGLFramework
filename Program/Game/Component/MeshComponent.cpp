#include "MeshComponent.h"

#include <GL/glew.h>
#include "../Actor.h"
#include "../Mesh.h"
#include "../VertexArray.h"

MeshComponent::MeshComponent(Actor* owner)
: mMesh(nullptr)
{
	owner->AddComponent(this);
}

MeshComponent::~MeshComponent()
{}

void MeshComponent::Update()
{
	if(mMesh){
		glDrawElements(GL_TRIANGLES, mMesh->mVertexArray->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
	}
}