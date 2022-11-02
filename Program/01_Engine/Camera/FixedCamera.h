#ifndef _FIXED_CAMERA_H_
#define _FIXED_CAMERA_H_

#include "Camera.h"
namespace tkl
{
class FixedCamera : public Camera
{
public:
	FixedCamera(int screenWidth, int screenHeight);
	virtual ~FixedCamera();

	virtual void Update() final;
};

} // namespace tkl

#endif