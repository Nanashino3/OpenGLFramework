#pragma once
#include "../../02_Library/Vector.h"
#include "../../02_Library/Quaternion.h"
#include "../../02_Library/Matrix.h"

class Camera
{
public:
	Camera(int screenWidth, int screenHeight)
	: mCamPos(0, 0, 0)
	, mTargetPos(tkl::Vector3::ZERO)
	, mUpVector(tkl::Vector3::UNITY)
	, mRotation(tkl::Quaternion())
	, mScreenWidth(screenWidth)
	, mScreenHeight(screenHeight)
	, mAngle(60.0f)
	, mAspect(static_cast<float>(screenWidth) / static_cast<float>(screenHeight))
	, mNear(1.0f)
	, mFar(5000.0f)
	, mViewProjection(tkl::Matrix())
	{}

	virtual ~Camera(){}
	
	virtual void Update() = 0;

	void SetPosition(const tkl::Vector3& pos){ mCamPos = pos; }
	tkl::Vector3 GetPosition() const{ return mCamPos; }

	void SetTargetPos(const tkl::Vector3& pos) { mTargetPos = pos; }
	tkl::Vector3 GetTargetPos() const{ return mTargetPos; }

	void SetRotation(const tkl::Quaternion& q){ mRotation = q; }
	tkl::Quaternion GetRotation() const{ return mRotation; }

	tkl::Matrix GetViewProjection() const { return mViewProjection; }

	tkl::Vector3 Front(){ return tkl::Vector3::Normalize(mTargetPos - mCamPos); }
	tkl::Vector3 Left()	{ return tkl::Vector3::Cross(tkl::Vector3::UNITY, Front()); }
	tkl::Vector3 Right(){ return tkl::Vector3::Cross(Front(), tkl::Vector3::UNITY); }

protected:
	tkl::Vector3 mCamPos;
	tkl::Vector3 mTargetPos;
	tkl::Vector3 mUpVector;
	tkl::Quaternion mRotation;

	int mScreenWidth;
	int mScreenHeight;
	float mAngle;	// 画角(角度指定)
	float mAspect;	// 縦横比(アスペクト比)
	float mNear;	// 表示範囲(最近距離)
	float mFar;		// 表示範囲(最遠距離)

	tkl::Matrix mViewProjection;
};