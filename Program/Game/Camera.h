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
	float mAngle;	// 画角(角度指定)
	float mAspect;	// 縦横比(アスペクト比)
	float mNear;	// 表示範囲(最近距離)
	float mFar;		// 表示範囲(最遠距離)

	Matrix mViewProjection;
};