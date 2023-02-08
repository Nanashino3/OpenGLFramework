//****************************************************************************
// �t�@�C�����FUiHitPoint(�q�b�g�|�C���gUI�N���X)
// ��@���@���F2023/01/30
#ifndef _UIHITPOINT_H_
#define _UIHITPOINT_H_

#include "UiBase.h"
#include <memory>

class AdvanceUnit;
namespace tkl
{
class Mesh;
class Camera;
class Vector3;
}

class UiHitPoint : public UiBase
{
public:
	UiHitPoint();
	virtual ~UiHitPoint();

	void Initialize(std::shared_ptr<AdvanceUnit> object);

	virtual void Update();
	virtual void Draw();

private:
	std::shared_ptr<tkl::Mesh> mTexture;
	std::shared_ptr<tkl::Mesh> mBackGroundTexture;
	std::shared_ptr<tkl::Camera> mCamera;
	std::shared_ptr<AdvanceUnit> mObject;

	int mScreenW, mScreenH;
	float mMaxHitPoint;
	float mRectW;

	std::shared_ptr<tkl::Camera> mTestCam;
};

#endif