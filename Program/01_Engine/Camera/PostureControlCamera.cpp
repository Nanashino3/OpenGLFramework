//****************************************************************************
// ファイル名：PostureControlCamera(姿勢制御カメラクラス)
// 作　成　日：2022/10/26
#include "PostureControlCamera.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

namespace tkl
{
PostureControlCamera::PostureControlCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
, mOnClickPos(tkl::Vector3::ZERO)
, mMovePos(tkl::Vector3::ZERO)
, mIsMouseMove(false)
{}

PostureControlCamera::~PostureControlCamera()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void PostureControlCamera::Update()
{
	// カメラズームイン・アウト(係数をかける)
	float scrollVal = static_cast<float>(tkl::Input::GetMouseScrollValue() * 10.0f);
	mCamPos += Front() * scrollVal;

	Input();
	Move();

	// 注視点と上方向ベクトルを更新
	mTargetPos = mCamPos + tkl::Vector3::TransformCoord(tkl::Vector3::NEG_UNITZ, mRotation);
	mUpVector = tkl::Vector3::TransformCoord(tkl::Vector3::UNITY, mRotation);

	// 行列
	mView = tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
	mProjection = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
}

//****************************************************************************
// 関数名：Input
// 概　要：入力処理
// 引　数：なし
// 戻り値：なし
// 詳　細：入力による処理を行う
//****************************************************************************
void PostureControlCamera::Input()
{
	// クリックした座標を記録する
	float clickPosX = 0, clickPosY = 0;
	if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(clickPosX, clickPosY);
		mOnClickPos = tkl::Vector3(clickPosX, clickPosY, 0.f);
	}
	// クリックした座標を初期化する
	if(tkl::Input::IsMouseReleaseTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		mOnClickPos = tkl::Vector3(tkl::Vector3::ZERO);
		mMovePos = tkl::Vector3(tkl::Vector3::ZERO);
	}

	// 現在位置を取得
	clickPosX = 0, clickPosY = 0;
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(clickPosX, clickPosY);

		// マウス移動しているかどうか
		mIsMouseMove = true;
		if(mMovePos.mX == clickPosX && mMovePos.mY == clickPosY){
			mIsMouseMove = !mIsMouseMove;
			mOnClickPos = mMovePos;
		}else{
			mMovePos.mX = static_cast<float>(clickPosX);
			mMovePos.mY = static_cast<float>(clickPosY);
		}
	}
}

//****************************************************************************
// 関数名：Move
// 概　要：移動処理
// 引　数：なし
// 戻り値：なし
// 詳　細：ガメラの移動制御
//****************************************************************************
void PostureControlCamera::Move()
{
	float dx = 0.0f, dy = 0.0f;
	if(mIsMouseMove){
		dx = (mOnClickPos.mX - mMovePos.mX) / (mScreenWidth >> 1);
		dy = (mOnClickPos.mY - mMovePos.mY) / (mScreenHeight >> 1);
	}

	tkl::Vector3 axis = tkl::Vector3::Cross(Front(), mUpVector);

	// 平行移動
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_CENTER)){
		mCamPos += axis * (10.0f * dx);
		mCamPos.mY -= 10.0f * dy;
	}

	// 視線移動
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_RIGHT)){
		mRotation *= tkl::Quaternion::RotationAxis(axis, tkl::ToRadian(dy * 5.0f));
		mRotation *= tkl::Quaternion::RotationAxis({0.f, 1.f, 0.f}, tkl::ToRadian(dx * 5.0f));
	}
}

} // namespace tkl