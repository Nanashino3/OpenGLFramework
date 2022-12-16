//****************************************************************************
// ファイル名：ScreenCamera(スクリーンカメラクラス)
// 作　成　日：2022/12/11
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