#include "MeshComponent.h"

#include <GL/glew.h>
#include "Mesh.h"
#include "Shader.h"

MeshComponent::MeshComponent()
: mMesh(nullptr)
{}

MeshComponent::~MeshComponent()
{}

void MeshComponent::Draw(Shader* shader)
{
	if(mMesh){
		Matrix wm = Matrix::CreateTranslation(mMesh->GetPosition());
		wm *= Matrix::CreateRotationFromQuaternion(mMesh->GetRotation());
		wm *= Matrix::CreateScale(mMesh->GetScale());
		shader->SetMatrixUniform("uWorldTransform", wm);

		VertexArray* va = mMesh->mVertexArray.get();
		va->Bind();
		glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
	}
}