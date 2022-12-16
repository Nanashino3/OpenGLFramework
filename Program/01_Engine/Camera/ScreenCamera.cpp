//****************************************************************************
// ファイル名：ScreenCamera(スクリーンカメラクラス)
// 作　成　日：2022/12/11
#include "ScreenCamera.h"

namespace tkl
{
ScreenCamera::ScreenCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
{}

ScreenCamera::~ScreenCamera()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void ScreenCamera::Update()
{
	float w = static_cast<float>(mScreenWidth >> 1);
	float h = static_cast<float>(mScreenHeight >> 1);
	mView = tkl::Matrix::CreateIdentity();
	mProjection = tkl::Matrix::CreateOrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);
}

} // namespace tkl