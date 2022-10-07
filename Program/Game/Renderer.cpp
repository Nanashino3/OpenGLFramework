#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VertexArray.h"
#include "../Library/Vector.h"

Renderer::Renderer()
{}

Renderer::~Renderer()
{}

void Renderer::Initialize()
{
	LoadShaders();
}

void Renderer::LoadShaders()
{
	mMeshShader = std::make_unique<Shader>();
	mMeshShader->LoadShader("Shader/LambertVert.glsl", "Shader/LambertFrag.glsl");
}

void Renderer::Draw(VertexArray* vertexArray)
{
	mMeshShader->ActiveShader();

	mMeshShader->SetMatrixUniform("uWorldTransform", mWorldTransform);
	mMeshShader->SetMatrixUniform("uViewProjection", mViewProjection);

	SetLightUniforms();

	vertexArray->Bind();
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexNum(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::SetLightUniforms()
{
	Vector3 camPos = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 ambientLight = Vector3(0.2f, 0.2f, 0.2f);
	Vector3 dirLightDirection = Vector3(0.0f, -1.0f, 0.0f);
	Vector3 dirLightDiffuseColor = Vector3(1.0f, 1.0f, 1.0f);

	mMeshShader->SetVectorUniform("uCameraPos", camPos);
	mMeshShader->SetVectorUniform("uAmbientColor", ambientLight);
	mMeshShader->SetVectorUniform("uDirLight.mDirection", dirLightDirection);
	mMeshShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLightDiffuseColor);
}