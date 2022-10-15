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

	void SetPosition(const Vector3& pos){ mCamPos = pos; }
	Vector3 GetPosition() const{ return mCamPos; }

	void SetTargetPos(const Vector3& pos) { mTargetPos = pos; }
	Vector3 GetTargetPos() const{ return mTargetPos; }

	void SetRotation(const Quaternion& q){ mRotation = q; }
	Quaternion GetRotation() const{ return mRotation; }

	Matrix GetViewProjection() const { return mViewProjection; }

	Vector3 Front() { return Vector3::Normalize(mTargetPos - mCamPos); }
	Vector3 Left()	{ return Vector3::Cross(Vector3::UNITY, Front()); }
	Vector3 Right() { return Vector3::Cross(Front(), Vector3::UNITY); }

	Vector3 Top()	{ return Vector3::Cross(Vector3::UNITX, Front()); }
	Vector3 Bottom(){ return Vector3::Cross(Front(), Vector3::UNITX); }

	Vector3 Up()	{ return Vector3::Cross(Right(), Front()); }

private:
	Vector3 mCamPos;
	Vector3 mTargetPos;
	Vector3 mUpVector;
	Vector3 mDragPos;
	Vector3 mRightVector;

	Quaternion mRotation;

	int mScreenWidth;
	int mScreenHeight;
	float mAngle;	// 画角(角度指定)
	float mAspect;	// 縦横比(アスペクト比)
	float mNear;	// 表示範囲(最近距離)
	float mFar;		// 表示範囲(最遠距離)

	Matrix mViewProjection;
};