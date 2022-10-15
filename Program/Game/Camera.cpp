#include "Camera.h"
#include "GameManager.h"
#include "../Library/Math.h"
#include "../Library/Input.h"

#include <iostream>

Camera::Camera(int screenWidth, int screenHeight)
: mCamPos(0, 0, 0)
, mTargetPos(Vector3::ZERO)
, mUpVector(Vector3::UNITY)
, mDragPos(Vector3::ZERO)
, mRotation(Quaternion())
, mScreenWidth(screenWidth)
, mScreenHeight(screenHeight)
, mAngle(60.0f)
, mNear(1.0f)
, mFar(5000.0f)
, mViewProjection(Matrix())
{
	mAspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
}

Camera::~Camera()
{}

void Camera::Update()
{
	// カメラズームイン・アウト
	float scrollVal = static_cast<float>(tkl::Input::GetMouseScrollValue() * 10.0f);
	mCamPos += Front() * scrollVal;

//	// 視線移動
//	if(tkl::Input::IsMouseInputTrigger(eMouse::MOUSE_INPUT_RIGHT) ||
//	   tkl::Input::IsMouseInputTrigger(eMouse::MOUSE_INPUT_LEFT)){
//		double posX, posY;
//		tkl::Input::GetMousePosition(&posX, &posY);
//		mDragPos.mX = static_cast<float>(posX);
//		mDragPos.mY = static_cast<float>(posY);
//	}
//
//	if(tkl::Input::IsMouseInput(eMouse::MOUSE_INPUT_RIGHT)){
//		double currentX, currentY;
//		tkl::Input::GetMousePosition(&currentX, &currentY);
//
//		float diffX = (mDragPos.mX - currentX) / (mScreenWidth >> 1);
//		mRotation *= Quaternion::RotationAxis(Up(), tkl::ToRadian(-1));

//		Vector3 temp2 = Vector3::Cross(Front(), Top());
//		float diffY = (mDragPos.mY - currentY) / (mScreenHeight >> 1);
//		mRotation *= Quaternion::RotationAxis(temp2, tkl::ToRadian(-1));
//	}
	mTargetPos = mCamPos + Vector3::TransformCoord({-1, -1, -1}, mRotation);

	// 行列
	mViewProjection  = Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}