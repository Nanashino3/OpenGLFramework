#include "FixedCamera.h"

namespace tkl
{
FixedCamera::FixedCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
{}

FixedCamera::~FixedCamera()
{}

void FixedCamera::Update()
{
	mView = tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
	mProjection = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
}

}