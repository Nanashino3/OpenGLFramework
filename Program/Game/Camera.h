#pragma once
#include "../Library/Vector.h"
#include "../Library/Matrix.h"

class Camera
{
public:
	Camera(int screenWidth, int screenHeight);
	virtual ~Camera();
	
	void Update();

	void SetPosition(const Vector3& pos){ mCamPos = pos; }
	Vector3 GetPosition() const{ return mCamPos; }

	Matrix GetViewProjection() const { return mViewProjection; }

private:
	Vector3 mCamPos;
	Vector3 mTargetPos;
	Vector3 mUpVector;

	float mAngle;	// ��p(�p�x�w��)
	float mAspect;	// �c����(�A�X�y�N�g��)
	float mNear;	// �\���͈�(�ŋߋ���)
	float mFar;		// �\���͈�(�ŉ�����)

	Matrix mViewProjection;
};