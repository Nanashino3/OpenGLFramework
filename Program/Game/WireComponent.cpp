#include "WireComponent.h"

#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
WireComponent::WireComponent()
{}

WireComponent::~WireComponent()
{}

void WireComponent::Draw(Shader* shader)
{
	if(mMesh){
		Matrix wm = Matrix::CreateTranslation(mMesh->GetPosition());
		shader->SetMatrixUniform("uWorldTransform", wm);

		VertexArray* va = mMesh->mVertexArray.get();
		va->Bind();
		glDrawArrays(GL_LINES, 0, va->GetVertexNum());
	}
}