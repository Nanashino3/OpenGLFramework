#include "Renderer.h"

#include "Camera.h"
#include "Shader.h"
#include "ShaderFactory.h"

Renderer::Renderer(Mesh* mesh, const char* shaderName)
: mMesh(mesh)
{
	mShader = ShaderFactory::GetInstance()->GetShader(shaderName);
}

Renderer::~Renderer()
{
	delete mShader;
}

// •`‰æŽwŽ¦
void Renderer::Draw(Camera* camera)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", camera->GetViewProjection());
}