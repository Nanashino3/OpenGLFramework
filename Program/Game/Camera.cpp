#include "Camera.h"
#include "GameManager.h"
#include "Renderer.h"

Camera::Camera(int screenWidth, int screenHeight)
: mCamPos(100.0f, 100.0f, 300.0f)
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
	mViewProjection  = Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}