#include "SpriteRenderer.h"

#include <GL/glew.h>
#include "Shader.h"
#include "Texture.h"
#include "../02_Library/Vector.h"

SpriteRenderer::SpriteRenderer(const char* shaderName)
: Renderer(shaderName)
{}

SpriteRenderer::~SpriteRenderer()
{}

void SpriteRenderer::ActualDraw(void* drawObject)
{
	if(!drawObject){ return; }

	Texture* texture = static_cast<Texture*>(drawObject);
	float textureW = static_cast<float>(texture->GetTextureWidth());
	float textureH = static_cast<float>(texture->GetTextureHeight());

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(texture->mPosition);
	wm *= tkl::Matrix::CreateScale(tkl::Vector3(textureW, textureH, 1.0f));
	mShader->SetMatrixUniform("uWorldTransform", wm);
	
	texture->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}