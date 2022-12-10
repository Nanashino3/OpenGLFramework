#ifndef _SCREENCAMERA_H_
#define _SCREENCAMERA_H_

#include "Camera.h"
namespace tkl
{
class ScreenCamera : public Camera
{
public:
	ScreenCamera(int screenWidth, int screenHeight);
	virtual ~ScreenCamera();

	virtual void Update() final;
};

} // namespace tkl

#endif