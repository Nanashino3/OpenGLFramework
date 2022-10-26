#include "PostureControlCamera.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

PostureControlCamera::PostureControlCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
, mOnClickPos(tkl::Vector3::ZERO)
, mMovePos(tkl::Vector3::ZERO)
, mIsMouseMove(false)
{}

PostureControlCamera::~PostureControlCamera()
{}

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
	mViewProjection  = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}

// 入力処理
void PostureControlCamera::Input()
{
	// クリックした座標を記録する
	int tempPosX = 0, tempPosY = 0;
	if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(&tempPosX, &tempPosY);
		mOnClickPos = tkl::Vector3(tempPosX, tempPosY, 0);
	}
	// クリックした座標を初期化する
	if(tkl::Input::IsMouseReleaseTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		mOnClickPos = tkl::Vector3(tkl::Vector3::ZERO);
		mMovePos = tkl::Vector3(tkl::Vector3::ZERO);
	}

	// 現在位置を取得
	tempPosX = 0, tempPosY = 0;
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(&tempPosX, &tempPosY);

		// マウス移動しているかどうか
		mIsMouseMove = true;
		if(mMovePos.mX == tempPosX && mMovePos.mY == tempPosY){
			mIsMouseMove = !mIsMouseMove;
			mOnClickPos = mMovePos;
		}else{
			mMovePos.mX = static_cast<float>(tempPosX);
			mMovePos.mY = static_cast<float>(tempPosY);
		}
	}
}

// 移動処理
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
		mRotation *= tkl::Quaternion::RotationAxis({ 0, 1, 0 }, tkl::ToRadian(dx * 5.0f));
	}
}