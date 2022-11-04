#include "SpriteRenderer.h"

#include <GL/glew.h>
#include "../Mesh.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../VertexArray.h"

namespace tkl
{
SpriteRenderer::SpriteRenderer(const char* shaderName)
: Renderer(shaderName)
{}

SpriteRenderer::~SpriteRenderer()
{}

#if 1
void SpriteRenderer::Draw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	Renderer::Draw(mesh);

	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if(texture){ texture->Bind(); }

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateScale(mesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}
#else
void SpriteRenderer::ActualDraw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }
	
	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if(!texture){ return; }

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateScale(tkl::Vector3(mesh->GetScale()));

	mShader->SetMatrixUniform("uWorldTransform", wm);
	
	if(texture){ texture->Bind(); }

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}
#endif

} // namespace tkl