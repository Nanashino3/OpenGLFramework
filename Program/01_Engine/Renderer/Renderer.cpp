//****************************************************************************
// ファイル名：Renderer(レンダラークラス)
// 作　成　日：2022/10/7
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
// 関数名：Draw
// 概　要：描画処理
// 引　数：arg1 メッシュ
// 戻り値：なし
// 詳　細：描画指示を行う
//****************************************************************************
void Renderer::Draw(std::shared_ptr<Mesh> mesh)
{
	mShader->ActiveShader();
	mShader->SetMatrixUniform("uViewProjection", mProjection * mView);
}

} // namespace tkl