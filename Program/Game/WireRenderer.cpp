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

void WireRenderer::ActualDraw(Mesh* mesh)
{
	if(!mesh){ return; }

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	VertexArray* va = mesh->mVertexArray.get();
	va->Bind();
	glDrawArrays(GL_LINES, 0, va->GetVertexNum());
}