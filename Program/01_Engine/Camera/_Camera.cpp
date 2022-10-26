#include "Camera.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

// デバッグ用
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