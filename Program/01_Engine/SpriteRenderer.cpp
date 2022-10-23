#include "SpriteRenderer.h"

#include <GL/glew.h>
#include "Texture.h"
SpriteRenderer::SpriteRenderer(const char* shaderName)
: Renderer(shaderName)
{}

SpriteRenderer::~SpriteRenderer()
{}

void SpriteRenderer::ActualDraw(void* drawObject)
{
	if(!drawObject){ return; }

	Texture* texture = static_cast<Texture*>(drawObject);
	texture->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}