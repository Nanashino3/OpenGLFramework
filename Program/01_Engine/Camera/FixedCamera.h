#pragma once

#include "Camera.h"
class FixedCamera : public Camera
{
public:
	FixedCamera(int screenWidth, int screenHeight);
	virtual ~FixedCamera();

	virtual void Update() final;
};