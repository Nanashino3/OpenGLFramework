#pragma once
#include "../Library/Vector.h"
#include "../Library/Matrix.h"

class Camera
{
public:
	Camera(int screenWidth, int screenHeight);
	virtual ~Camera();

	Vector3 mCamPos;
	Vector3 mTargetPos;
	Vector3 mUpVector;
	
	void Update();
	Matrix GetViewProjection() const { return mViewProjection; }

private:
	float mAngle;	// ��p(�p�x�w��)
	float mAspect;	// �c����(�A�X�y�N�g��)
	float mNear;	// �\���͈�(�ŋߋ���)
	float mFar;		// �\���͈�(�ŉ�����)

	Matrix mViewProjection;
};