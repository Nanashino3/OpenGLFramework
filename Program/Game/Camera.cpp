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
, mRotation(tkl::Quaternion())
, mScreenWidth(screenWidth)
, mScreenHeight(screenHeight)
, mAngle(60.0f)
, mAspect(static_cast<float>(screenWidth)/static_cast<float>(screenHeight))
, mNear(1.0f)
, mFar(5000.0f)
, mViewProjection(tkl::Matrix())
{}

Camera::~Camera()
{}

void Camera::Update()
{
	// カメラズームイン・アウト(係数をかける)
	float scrollVal = static_cast<float>(tkl::Input::GetMouseScrollValue() * 10.0f);
	mCamPos += Front() * scrollVal;

//	// クリックした場所を記録
//	if(tkl::Input::IsMouseInputTrigger(eMouse::MOUSE_INPUT_CENTER) ||
//	   tkl::Input::IsMouseInputTrigger(eMouse::MOUSE_INPUT_RIGHT)){
//		int x = 0, y = 0;
//		tkl::Input::GetMousePosition(&x, &y);
//		mOnClickPos.mX = x, mOnClickPos.mY = y;
//	}
	
	// カメラ移動
	CameraMove();

	// 視線移動
	LookMove();
	mTargetPos = mCamPos + tkl::Vector3::TransformCoord({-1, -1, -1}, mRotation);
	mUpVector = tkl::Vector3::TransformCoord(tkl::Vector3::UNITY, mRotation);

	// 行列
	mViewProjection  = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}

// カメラ移動(TODO：マウス操作で移動できるようにする)
void Camera::CameraMove()
{
	if(tkl::Input::IsKeyDown(eKeys::KB_W)){
		mCamPos.mY += 2.0f;
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_S)){
		mCamPos.mY -= 2.0f;
	}

	if(tkl::Input::IsKeyDown(eKeys::KB_A)){
		mCamPos += Left() * 2.0f;
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_D)){
		mCamPos += Right() * 2.0f;
	}
}

// 視線移動(TODO：マウスで操作できるようにする)
void Camera::LookMove()
{
	if(tkl::Input::IsKeyDown(eKeys::KB_UP)){
		tkl::Vector3 axis = tkl::Vector3::Cross(Front(), mUpVector);
		mRotation *= tkl::Quaternion::RotationAxis(axis, tkl::ToRadian(1));
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_DOWN)){
		tkl::Vector3 axis = tkl::Vector3::Cross(Front(), mUpVector);
		mRotation *= tkl::Quaternion::RotationAxis(axis, tkl::ToRadian(-1));
	}

	// 左右視線移動
	if(tkl::Input::IsKeyDown(eKeys::KB_LEFT)){
		mRotation *= tkl::Quaternion::RotationAxis({0, 1, 0}, tkl::ToRadian(1));
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_RIGHT)){
		mRotation *= tkl::Quaternion::RotationAxis({0, 1, 0}, tkl::ToRadian(-1));
	}
}