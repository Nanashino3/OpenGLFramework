#include "WireRenderer.h"

#include <GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "../Library/Matrix.h"
WireRenderer::WireRenderer(Mesh* mesh, const char* shaderName)
: Renderer(mesh, shaderName)
{
	mesh->SetRenderer(this);
}

WireRenderer::~WireRenderer()
{}

void WireRenderer::Draw(Camera* camera)
{
	if(!mMesh){ return; }

	Renderer::Draw(camera);

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mMesh->GetPosition());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	VertexArray* va = mMesh->mVertexArray.get();
	va->Bind();
	glDrawArrays(GL_LINES, 0, va->GetVertexNum());
}