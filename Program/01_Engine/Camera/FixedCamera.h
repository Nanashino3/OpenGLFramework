#pragma once

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

}