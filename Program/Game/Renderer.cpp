#include "Renderer.h"

#include "Camera.h"
#include "Shader.h"
#include "ShaderFactory.h"

Renderer::Renderer(Mesh* mesh, const char* shaderName)
{
	mShader = ShaderFactory::GetInstance()->GetShader(shaderName);
}

Renderer::~Renderer()
{
	delete mShader;
}

// •`‰æw¦
void Renderer::Draw(Mesh* mesh, Camera* camera)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", camera->GetViewProjection());

	// ‹ïÛƒNƒ‰ƒX‘¤‚Ì•`‰æˆ—
	ActualDraw(mesh);
}