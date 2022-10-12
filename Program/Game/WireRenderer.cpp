#include "WireRenderer.h"

#include <GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "../Library/Matrix.h"
WireRenderer::WireRenderer(Mesh* mesh)
: Renderer(mesh)
{}

WireRenderer::~WireRenderer()
{}

void WireRenderer::Draw(Camera* camera)
{
	if(!mMesh){ return; }

	Renderer::Draw(camera);

	Matrix wm = Matrix::CreateTranslation(mMesh->GetPosition());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	VertexArray* va = mMesh->mVertexArray.get();
	va->Bind();
	glDrawArrays(GL_LINES, 0, va->GetVertexNum());
}