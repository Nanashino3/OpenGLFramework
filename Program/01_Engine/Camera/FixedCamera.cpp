//****************************************************************************
// ファイル名：FixedCamera(固定カメラクラス)
// 作　成　日：2022/10/26
#include "FixedCamera.h"

namespace tkl
{
FixedCamera::FixedCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
{}

FixedCamera::~FixedCamera()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void FixedCamera::Update()
{
	mView = tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
	mProjection = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
}

} // namespace tkl