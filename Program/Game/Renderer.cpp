#include "Renderer.h"

#include "Camera.h"
#include "Shader.h"

Renderer::Renderer(Mesh* mesh)
: mMesh(mesh)
, mShader(nullptr)
{}

Renderer::~Renderer()
{
	delete mShader;
}

// �V�F�[�_�̓ǂݍ���
void Renderer::LoadShader(const char* vertexFile, const char* fragFile)
{
	mShader = new Shader();
	mShader->LoadShader(vertexFile, fragFile);
}

// �`��w��
void Renderer::Draw(Camera* camera)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", camera->GetViewProjection());
}