#include "Camera.h"
#include "GameManager.h"
#include "Renderer.h"
#include "../Library/Input.h"

#include <iostream>

Camera::Camera(int screenWidth, int screenHeight)
: mCamPos(0, 0, 0)
, mTargetPos(Vector3::ZERO)
, mUpVector(Vector3::UNITY)
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
	double scrollVal = tkl::Input::GetMouseScrollValue() * 10.0f;
	mCamPos.mX += scrollVal;
	mCamPos.mY += scrollVal;
	mCamPos.mZ += scrollVal;

	// �����ړ�
	mTargetPos = mCamPos + Vector3::TransformCoord({-1, -1, -1}, mRotation);

	// �s��
	mViewProjection  = Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}