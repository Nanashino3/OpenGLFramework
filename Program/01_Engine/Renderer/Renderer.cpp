#include "Renderer.h"

#include "../Shader.h"
#include "../ShaderFactory.h"

Renderer::Renderer(const char* shaderName)
{
	mShader = ShaderFactory::GetInstance()->GetShader(shaderName);
}

Renderer::~Renderer()
{}

// �`��w��
void Renderer::Draw(void* drawObject)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", mViewProjection);

	// ��ۃN���X���̕`�揈��
	ActualDraw(drawObject);
}