//****************************************************************************
// �t�@�C�����FMeshRenderer(���b�V�������_���[�N���X)
// ��@���@���F2022/10/13
#include "MeshRenderer.h"

#include <GL/glew.h>
#include "../Shader.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/Texture.h"
#include "../Geometry/VertexArray.h"
#include "../Geometry/Material.h"

namespace tkl
{
MeshRenderer::MeshRenderer(const char* shaderName)
: Renderer(shaderName)
{}

MeshRenderer::~MeshRenderer()
{}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���Farg1 ���b�V��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`��w�����s��
//****************************************************************************
void MeshRenderer::Draw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	Renderer::Draw(mesh);

	// �����ݒ�
	SetLightUniforms(mesh);

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateRotationFromQuaternion(mesh->GetRotation());
	wm *= tkl::Matrix::CreateScale(mesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if(texture != nullptr){
		if(mesh->GetIsBlend()){
			glEnable(GL_BLEND);
			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		}
		texture->Bind();
	}

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	
	if(mesh->GetIsWireframe()){ glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}

//****************************************************************************
// �֐����FSetLightUniforms
// �T�@�v�F���C�e�B���O�̐ݒ�
// ���@���Farg1 ���b�V��
// �߂�l�F�Ȃ�
// �ځ@�ׁF���C�f�B���O��ݒ肷��(����Œ�)
//****************************************************************************
void MeshRenderer::SetLightUniforms(std::shared_ptr<Mesh> mesh)
{
	// �}�e���A����ݒ�
	std::shared_ptr<Material> mtl = mesh->GetMaterial();
	mShader->SetVectorUniform("uMaterial.mAmbient", mtl->GetAmbient());
	mShader->SetVectorUniform("uMaterial.mDiffuse", mtl->GetDiffuse());

	// �����̐ݒ�
	mShader->SetVectorUniform("uAmbientColor", tkl::Vector3(0.2f, 0.2f, 0.2f));
	mShader->SetVectorUniform("uDirLight.mDirection", tkl::Vector3(0.0f, -0.707f, -0.707f));
	mShader->SetVectorUniform("uDirLight.mDiffuseColor", tkl::Vector3(0.78f, 0.88f, 1.0f));
}

} // namespace tkl