//****************************************************************************
// ファイル名：FixedCamera(固定カメラクラス)
// 作　成　日：2022/10/26
#ifndef _FIXEDCAMERA_H_
#define _FIXEDCAMERA_H_

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