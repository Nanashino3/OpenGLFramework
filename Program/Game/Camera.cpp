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
	// �J�����Y�[���C���E�A�E�g
	float scrollVal = static_cast<float>(tkl::Input::GetMouseScrollValue() * 10.0f);
	mCamPos += Front() * scrollVal;

	// �J�����ړ�
	CameraMove();

	// �����ړ�
	LookMove();
	mTargetPos = mCamPos + Vector3::TransformCoord({ -1, -1, -1 }, mRotation);

	// �s��
	mViewProjection  = Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}

// �J�����ړ�(TODO�F�}�E�X����ňړ��ł���悤�ɂ���)
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

// �����ړ�(TODO�F�}�E�X�ő���ł���悤�ɂ���)
void Camera::LookMove()
{
	// �㉺�����ړ�
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

	// ���E�����ړ�
	if(tkl::Input::IsKeyDown(eKeys::KB_LEFT)){
		mRotation *= Quaternion::RotationAxis({ 0, 1, 0 }, tkl::ToRadian(1));
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_RIGHT)){
		mRotation *= Quaternion::RotationAxis({ 0, 1, 0 }, tkl::ToRadian(-1));
	}
}