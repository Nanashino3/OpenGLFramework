#include "Camera.h"
#include "GameManager.h"
#include "../Library/Math.h"
#include "../Library/Input.h"

#include <iostream>

Camera::Camera(int screenWidth, int screenHeight)
: mCamPos(0, 0, 0)
, mTargetPos(Vector3::ZERO)
, mUpVector(Vector3::UNITY)
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

	// カメラ移動
	CameraMove();

	// 視線移動
	LookMove();
	mTargetPos = mCamPos + Vector3::TransformCoord({ -1, -1, -1 }, mRotation);

	// 行列
	mViewProjection  = Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
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
	// 上下視線移動
	if(tkl::Input::IsKeyDownTrigger(eKeys::KB_UP) || 
	   tkl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)){
		mUpAndDownVec = Vector3::Cross(Front(), Up());
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_UP)){
		mRotation *= Quaternion::RotationAxis(mUpAndDownVec, tkl::ToRadian(1));
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_DOWN)){
		mRotation *= Quaternion::RotationAxis(mUpAndDownVec, tkl::ToRadian(-1));
	}
	std::cout << "x : " << mUpAndDownVec.mX << " y : " << mUpAndDownVec.mY << " z : " << mUpAndDownVec.mZ << std::endl;

	// 左右視線移動
	if(tkl::Input::IsKeyDown(eKeys::KB_LEFT)){
		mRotation *= Quaternion::RotationAxis({ 0, 1, 0 }, tkl::ToRadian(1));
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_RIGHT)){
		mRotation *= Quaternion::RotationAxis({ 0, 1, 0 }, tkl::ToRadian(-1));
	}
}