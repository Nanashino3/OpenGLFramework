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

	float mAngle;	// 画角(角度指定)
	float mAspect;	// 縦横比(アスペクト比)
	float mNear;	// 表示範囲(最近距離)
	float mFar;		// 表示範囲(最遠距離)

	Matrix mViewProjection;
};