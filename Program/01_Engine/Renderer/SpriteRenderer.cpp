#include "SpriteRenderer.h"

#include <GL/glew.h>
#include "../Mesh.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../VertexArray.h"
#include "../../02_Library/Vector.h"

SpriteRenderer::SpriteRenderer(const char* shaderName)
: Renderer(shaderName)
{}

SpriteRenderer::~SpriteRenderer()
{}

void SpriteRenderer::ActualDraw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }
	
	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if(!texture){ return; }

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateScale(tkl::Vector3(texture->GetTextureWidth(), texture->GetTextureHeight(), 1.0f));
	mShader->SetMatrixUniform("uWorldTransform", wm);
	
	if(texture){ texture->Bind(); }

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}