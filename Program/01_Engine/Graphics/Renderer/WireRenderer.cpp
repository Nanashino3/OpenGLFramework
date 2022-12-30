//****************************************************************************
// �t�@�C�����FWireRenderer(���C���[�����_���[�N���X)
// ��@���@���F2022/10/13
#include "WireRenderer.h"

#include <GL/glew.h>
#include "../Shader.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/VertexArray.h"

namespace tkl
{
WireRenderer::WireRenderer(const char* shaderName)
: Renderer(shaderName)
{}

WireRenderer::~WireRenderer()
{}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���Farg1 ���b�V��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`��w�����s��
//****************************************************************************
void WireRenderer::Draw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	Renderer::Draw(mesh);

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateRotationFromQuaternion(mesh->GetRotation());
	wm *= tkl::Matrix::CreateScale(mesh->GetScale());
	mShader->SetMatrixUniform("uWorldTransform", wm);

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawArrays(GL_LINES, 0, va->GetVertexNum());
}

} // namespace tkl