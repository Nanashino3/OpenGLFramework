#ifndef _UICOLLECT_H_
#define _UICOLLECT_H_

#include "UiBase.h"
#include <memory>

namespace tkl
{
class Mesh;
class Camera;
}

class UiCollect : public UiBase
{
public:
	UiCollect();
	virtual ~UiCollect();

	void Initialize();
	void SetTotalCost(int value){ mTotalCost = value; }

	virtual void Update();
	virtual void Draw();

private:
	float mStartPosX, mStartPosY;
	int mTotalCost;

	std::shared_ptr<tkl::Mesh> mMesh;
	std::shared_ptr<tkl::Camera> mCamera;
};

#endif