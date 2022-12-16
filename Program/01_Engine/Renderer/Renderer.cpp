//****************************************************************************
// �t�@�C�����FRenderer(�����_���[�N���X)
// ��@���@���F2022/10/7
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

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���Farg1 ���b�V��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`��w�����s��
//****************************************************************************
void Renderer::Draw(std::shared_ptr<Mesh> mesh)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", mProjection * mView);
}

} // namespace tkl