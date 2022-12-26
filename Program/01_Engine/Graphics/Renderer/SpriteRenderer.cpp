//****************************************************************************
// �t�@�C�����FSpriteRenderer(�X�v���C�g�����_���[�N���X)
// ��@���@���F2022/10/26
#include "SpriteRenderer.h"

#include <iostream>
#include <GL/glew.h>
#include "../Shader.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/Texture.h"
#include "../Geometry/VertexArray.h"

namespace tkl
{
SpriteRenderer::SpriteRenderer(const char* shaderName)
: Renderer(shaderName)
{}

SpriteRenderer::~SpriteRenderer()
{}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���Farg1 ���b�V��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`��w�����s��
//****************************************************************************
void SpriteRenderer::Draw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	Renderer::Draw(mesh);

	std::shared_ptr<Texture> texture = mesh->GetTexture();
	if(!texture){
		std::cerr << "Failed No Texture." << std::endl;
		exit(1);
	}

	texture->Bind();

	tkl::Vector3 scale = mesh->GetScale();
	float scaleX = static_cast<float>(texture->GetTextureWidth() * scale.mX);
	float scaleY = static_cast<float>(texture->GetTextureHeight() * scale.mY);

	tkl::Matrix wm = tkl::Matrix::CreateTranslation(mesh->GetPosition());
	wm *= tkl::Matrix::CreateScale(tkl::Vector3(scaleX, scaleY, scale.mZ));
	mShader->SetMatrixUniform("uWorldTransform", wm);
	mShader->SetFloatUniform("uAlpha", mesh->GetAlpha());

	std::shared_ptr<VertexArray> va = mesh->GetVertex();
	va->Bind();
	glDrawElements(GL_TRIANGLES, va->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
}

} // namespace tkl