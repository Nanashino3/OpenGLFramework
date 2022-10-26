#include "Renderer.h"

#include "../Shader.h"
#include "../ShaderFactory.h"

Renderer::Renderer(const char* shaderName)
{
	mShader = ShaderFactory::GetInstance()->GetShader(shaderName);
}

Renderer::~Renderer()
{}

// •`‰æw¦
void Renderer::Draw(void* drawObject)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", mViewProjection);

	// ‹ïÛƒNƒ‰ƒX‘¤‚Ì•`‰æˆ—
	ActualDraw(drawObject);
}