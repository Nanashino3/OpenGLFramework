#pragma once
#include "../Library/Vector.h"
#include "../Library/Quaternion.h"
#include "../Library/Matrix.h"

class Camera
{
public:
	Camera(int screenWidth, int screenHeight);
	virtual ~Camera();
	
	void Update();

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

//	Vector3 Top()	{ return Vector3::Cross(Vector3::UNITX, Front()); }
//	Vector3 Bottom(){ return Vector3::Cross(Front(), Vector3::UNITX); }
//	tkl::Vector3 Up()	{ return tkl::Vector3::Cross(Right(), Front()); }

private:
	void CameraMove();
	void LookMove();

private:
	tkl::Vector3 mCamPos;
	tkl::Vector3 mTargetPos;
	tkl::Vector3 mUpVector;
//	tkl::Vector3 mUpAndDownVec;

	tkl::Vector3 mOnClickPos;

	tkl::Quaternion mRotation;

	int mScreenWidth;
	int mScreenHeight;
	float mAngle;	// 画角(角度指定)
	float mAspect;	// 縦横比(アスペクト比)
	float mNear;	// 表示範囲(最近距離)
	float mFar;		// 表示範囲(最遠距離)

	tkl::Matrix mViewProjection;
};