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

void SpriteRenderer::ActualDraw(void* drawObject)
{
	if(!drawObject){ return; }

//	Texture* texture = static_cast<Texture*>(drawObject);
	Mesh* mesh = static_cast<Mesh*>(drawObject);

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateScale(mesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);
	
	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if(texture){ texture->Bind(); }

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}