#include "Camera.h"
#include "GameManager.h"
#include "../Library/Math.h"
#include "../Library/Input.h"

#include <iostream>
#include <iomanip>

Camera::Camera(int screenWidth, int screenHeight)
: mCamPos(0, 0, 0)
, mTargetPos(tkl::Vector3::ZERO)
, mUpVector(tkl::Vector3::UNITY)
, mOnClickPos(tkl::Vector3::ZERO)
, mMovePos(tkl::Vector3::ZERO)
, mRotation(tkl::Quaternion())
, mScreenWidth(screenWidth)
, mScreenHeight(screenHeight)
, mAngle(60.0f)
, mAspect(static_cast<float>(screenWidth)/static_cast<float>(screenHeight))
, mNear(1.0f)
, mFar(5000.0f)
, mViewProjection(tkl::Matrix())
, mIsMouseMove(false)
{}

Camera::~Camera()
{}

void Camera::Update()
{
	// カメラズームイン・アウト(係数をかける)
	float scrollVal = static_cast<float>(tkl::Input::GetMouseScrollValue() * 10.0f);
	mCamPos += Front() * scrollVal;
	
	Input();
	Move();

	mTargetPos = mCamPos + tkl::Vector3::TransformCoord(tkl::Vector3::NEG_UNITZ, mRotation);
	mUpVector = tkl::Vector3::TransformCoord(tkl::Vector3::UNITY, mRotation);

	// 行列
	mViewProjection  = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}

void Camera::Input()
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
void Camera::Move()
{
	float dx = 0.0f, dy = 0.0f;
	if(mIsMouseMove){
		dx = (mOnClickPos.mX - mMovePos.mX) / (mScreenWidth >> 1);
		dy = (mOnClickPos.mY - mMovePos.mY) / (mScreenHeight >> 1);
	}
	std::cout << "dx : " << std::setw(5) << dx << " dy : " << dy << std::endl;

	// 平行移動
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_CENTER)){
		mCamPos.mX += Front().mX + dx * 10.0f;
		mCamPos.mY += Front().mY - dy * 10.0f;
	}

	// 視線移動
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_RIGHT)){
		tkl::Vector3 axis = tkl::Vector3::Cross(Front(), mUpVector);
		mRotation *= tkl::Quaternion::RotationAxis(axis, tkl::ToRadian(dy * 5.0f));
		mRotation *= tkl::Quaternion::RotationAxis({ 0, 1, 0 }, tkl::ToRadian(dx * 5.0f));
	}
}