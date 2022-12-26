//****************************************************************************
// ファイル名：SpriteRenderer(スプライトレンダラークラス)
// 作　成　日：2022/10/26
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
// 関数名：Draw
// 概　要：描画処理
// 引　数：arg1 メッシュ
// 戻り値：なし
// 詳　細：描画指示を行う
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