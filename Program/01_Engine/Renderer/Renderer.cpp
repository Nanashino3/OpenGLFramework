#include "Renderer.h"

#include "../Shader.h"
#include "../ShaderFactory.h"

namespace tkl
{
Renderer::Renderer(const char* shaderName)
{
	mShader = ShaderFactory::GetInstance()->GetShader(shaderName);
}

Renderer::~Renderer()
{}

// •`‰æw¦
void Renderer::Draw(std::shared_ptr<Mesh> mesh)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", mViewProjection);
}

} // namespace tkl