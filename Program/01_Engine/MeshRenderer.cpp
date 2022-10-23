#include "MeshRenderer.h"

#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "../02_Library/Vector.h"
#include "../02_Library/Matrix.h"
MeshRenderer::MeshRenderer(const char* shaderName)
: Renderer(shaderName)
{}

MeshRenderer::~MeshRenderer()
{}

void MeshRenderer::ActualDraw(void* drawObject)
{
	if (!drawObject) { return; }

	Mesh* mesh = static_cast<Mesh*>(drawObject);

	SetLightUniforms();

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateRotationFromQuaternion(mesh->GetRotation());
	wm *= tkl::Matrix::CreateScale(mesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	VertexArray* va = mesh->mVertexArray.get();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}

// ライティングの設定
void MeshRenderer::SetLightUniforms()
{
	tkl::Vector3 camPos = tkl::Vector3(0.0f, 1.0f, 0.0f);
	tkl::Vector3 ambientLight = tkl::Vector3(0.2f, 0.2f, 0.2f);
	tkl::Vector3 dirLightDirection = tkl::Vector3(0.0f, -1.0f, 0.0f);
	tkl::Vector3 dirLightDiffuseColor = tkl::Vector3(1.0f, 1.0f, 1.0f);

	mShader->SetVectorUniform("uCameraPos", camPos);
	mShader->SetVectorUniform("uAmbientColor", ambientLight);
	mShader->SetVectorUniform("uDirLight.mDirection", dirLightDirection);
	mShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLightDiffuseColor);
}