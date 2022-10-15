#include "MeshRenderer.h"

#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "../Library/Vector.h"
#include "../Library/Matrix.h"
MeshRenderer::MeshRenderer(Mesh* mesh, const char* shaderName)
: Renderer(mesh, shaderName)
{
	mesh->SetRenderer(this);
}

MeshRenderer::~MeshRenderer()
{}

// ライティングの設定
void MeshRenderer::SetLightUniforms()
{
	Vector3 camPos = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 ambientLight = Vector3(0.2f, 0.2f, 0.2f);
	Vector3 dirLightDirection = Vector3(0.0f, -1.0f, 0.0f);
	Vector3 dirLightDiffuseColor = Vector3(1.0f, 1.0f, 1.0f);

	mShader->SetVectorUniform("uCameraPos", camPos);
	mShader->SetVectorUniform("uAmbientColor", ambientLight);
	mShader->SetVectorUniform("uDirLight.mDirection", dirLightDirection);
	mShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLightDiffuseColor);
}

void MeshRenderer::Draw(Camera* camera)
{
	if(!mMesh){ return; }

	Renderer::Draw(camera);
	SetLightUniforms();

	Matrix wm = Matrix::CreateTranslation(mMesh->GetPosition());
	wm *= Matrix::CreateRotationFromQuaternion(mMesh->GetRotation());
	wm *= Matrix::CreateScale(mMesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	VertexArray* va = mMesh->mVertexArray.get();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}