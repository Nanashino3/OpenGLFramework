#include "WireRenderer.h"

#include <GL/glew.h>
#include "../Mesh.h"
#include "../Shader.h"
#include "../VertexArray.h"

namespace tkl
{
WireRenderer::WireRenderer(const char* shaderName)
: Renderer(shaderName)
{}

WireRenderer::~WireRenderer()
{}

void WireRenderer::Draw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }

	Renderer::Draw(mesh);

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawArrays(GL_LINES, 0, va->GetVertexNum());
}

} // namespace tkl