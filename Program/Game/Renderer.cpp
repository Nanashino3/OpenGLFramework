#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Shader.h"
#include "MeshComponent.h"
#include "WireComponent.h"
#include "../Library/Vector.h"

Renderer::Renderer()
: mMeshShader(nullptr)
, mWireframeShader(nullptr)
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

	mWireframeShader = std::make_unique<Shader>();
	mWireframeShader->LoadShader("Shader/PointVert.glsl", "Shader/PointFrag.glsl");
}

void Renderer::Draw(Camera* camera)
{
	// メッシュ用シェーダ
	mMeshShader->ActiveShader();
	SetLightUniforms(mMeshShader.get());
	mMeshShader->SetMatrixUniform("uViewProjection", camera->GetViewProjection());
	for(auto meshComponent : mMeshComponents){
		meshComponent->Draw(mMeshShader.get());
	}

	// ワイヤーフレーム用シェーダ
	mWireframeShader->ActiveShader();
	mWireframeShader->SetMatrixUniform("uViewProjection", camera->GetViewProjection());
	for (auto wireComponent : mWireComponents) {
		wireComponent->Draw(mWireframeShader.get());
	}
}

void Renderer::SetLightUniforms(Shader* shader)
{
	Vector3 camPos = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 ambientLight = Vector3(0.2f, 0.2f, 0.2f);
	Vector3 dirLightDirection = Vector3(0.0f, -1.0f, 0.0f);
	Vector3 dirLightDiffuseColor = Vector3(1.0f, 1.0f, 1.0f);

	shader->SetVectorUniform("uCameraPos", camPos);
	shader->SetVectorUniform("uAmbientColor", ambientLight);
	shader->SetVectorUniform("uDirLight.mDirection", dirLightDirection);
	shader->SetVectorUniform("uDirLight.mDiffuseColor", dirLightDiffuseColor);
}