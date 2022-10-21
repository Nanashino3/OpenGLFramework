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

private:
	void Input();
	void Move();

private:
	tkl::Vector3 mCamPos;
	tkl::Vector3 mTargetPos;
	tkl::Vector3 mUpVector;

	tkl::Vector3 mOnClickPos;
	tkl::Vector3 mMovePos;

	tkl::Quaternion mRotation;

	int mScreenWidth;
	int mScreenHeight;
	float mAngle;	// ��p(�p�x�w��)
	float mAspect;	// �c����(�A�X�y�N�g��)
	float mNear;	// �\���͈�(�ŋߋ���)
	float mFar;		// �\���͈�(�ŉ�����)

	tkl::Matrix mViewProjection;

	bool mIsMouseMove;
};