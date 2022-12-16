//****************************************************************************
// ファイル名：MeshRenderer(メッシュレンダラークラス)
// 作　成　日：2022/10/13
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

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：arg1 メッシュ
// 戻り値：なし
// 詳　細：描画指示を行う
//****************************************************************************
void MeshRenderer::Draw(std::shared_ptr<Mesh> mesh)
{
	if(!mesh){ return; }

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	Renderer::Draw(mesh);

	// 光源設定
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

//****************************************************************************
// 関数名：SetLightUniforms
// 概　要：ライティングの設定
// 引　数：arg1 メッシュ
// 戻り値：なし
// 詳　細：ライディングを設定する(現状固定)
//****************************************************************************
void MeshRenderer::SetLightUniforms()
{
//	tkl::Matrix invView = tkl::Matrix::CreateInverseMatrix(mView);
//	tkl::Vector3 camPos = tkl::Vector3(invView._14, invView._24, invView._34);
	tkl::Vector3 ambientLight = tkl::Vector3(0.2f, 0.2f, 0.2f);
	tkl::Vector3 dirLightDirection = tkl::Vector3(0.0f, -0.707f, -0.707f);
	tkl::Vector3 dirLightDiffuseColor = tkl::Vector3(0.78f, 0.88f, 1.0f);

//	mShader->SetVectorUniform("uCameraPos", camPos);
	mShader->SetVectorUniform("uAmbientColor", ambientLight);
	mShader->SetVectorUniform("uDirLight.mDirection", dirLightDirection);
	mShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLightDiffuseColor);
}

} // namespace tkl