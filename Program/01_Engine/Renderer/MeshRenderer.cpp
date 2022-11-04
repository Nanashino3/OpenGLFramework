#include "MeshRenderer.h"

#include <GL/glew.h>
#include "../Mesh.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../VertexArray.h"

namespace tkl
{
MeshRenderer::MeshRenderer(const char* shaderName)
: Renderer(shaderName)
{}

MeshRenderer::~MeshRenderer()
{}

#if 1
void MeshRenderer::Draw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	Renderer::Draw(mesh);

	// �����ݒ�
	SetLightUniforms();

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateRotationFromQuaternion(mesh->GetRotation());
	wm *= tkl::Matrix::CreateScale(mesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if (texture) { texture->Bind(); }

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}
#else
void MeshRenderer::ActualDraw(std::shared_ptr<Mesh> mesh)
{
	if (!mesh) { return; }

	// �����ݒ�
	SetLightUniforms();

	// ���[���h���W�v�Z
	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateRotationFromQuaternion(mesh->GetRotation());
	wm *= tkl::Matrix::CreateScale(mesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	// �e�N�X�`����L�������邩
	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if(texture){ texture->Bind(); }

	// �`���L��������
	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}
#endif

// ���C�e�B���O�̐ݒ�
void MeshRenderer::SetLightUniforms()
{
	//*****************************************************
	// TODO�F�J�����ʒu�͊O����ݒ�ł���悤�ɂ���
	tkl::Vector3 camPos = tkl::Vector3(0.0f, 1.0f, 0.0f);
	mShader->SetVectorUniform("uCameraPos", camPos);
	//*****************************************************

	tkl::Vector3 ambientLight = tkl::Vector3(0.2f, 0.2f, 0.2f);
	tkl::Vector3 dirLightDirection = tkl::Vector3(0.0f, -1.0f, 0.0f);
	tkl::Vector3 dirLightDiffuseColor = tkl::Vector3(0.8f, 0.8f, 0.8f);

	mShader->SetVectorUniform("uAmbientColor", ambientLight);
	mShader->SetVectorUniform("uDirLight.mDirection", dirLightDirection);
	mShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLightDiffuseColor);
}

} // namespace tkl