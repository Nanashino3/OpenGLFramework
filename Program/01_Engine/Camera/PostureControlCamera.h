#ifndef _POSTURECONTROLCAMERA_H_
#define _POSTURECONTROLCAMERA_H_

#include "Camera.h"
#include "../../02_Library/Vector.h"
#include "../../02_Library/Quaternion.h"

namespace tkl
{
class PostureControlCamera : public Camera
{
public:
	PostureControlCamera(int screenWidth, int screenHeight);
	virtual ~PostureControlCamera();

	virtual void Update() final;

private:
	void Input();
	void Move();

private:
	tkl::Vector3 mOnClickPos;
	tkl::Vector3 mMovePos;
	bool mIsMouseMove;
};

} // namespace tkl

#endif