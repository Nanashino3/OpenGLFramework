//****************************************************************************
// ファイル名：WireRenderer(ワイヤーレンダラークラス)
// 作　成　日：2022/10/13
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
// 関数名：Draw
// 概　要：描画処理
// 引　数：arg1 メッシュ
// 戻り値：なし
// 詳　細：描画指示を行う
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