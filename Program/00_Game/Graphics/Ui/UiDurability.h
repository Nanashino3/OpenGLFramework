#ifndef _UIDURABILITY_H_
#define _UIDURABILITY_H_

#include "UiBase.h"
#include <memory>
#include <vector>

namespace tkl
{
class Mesh;
class Camera;
}

class UiDurability : public UiBase
{
public:
	UiDurability(int durability);
	virtual ~UiDurability();

	void Initialize();
	void SetDurability(int value){ mDurability = value; }

	virtual void Update();
	virtual void Draw();

private:
	int mDurability;
	
	std::shared_ptr<tkl::Camera> mCamera;
	std::shared_ptr<tkl::Mesh> mTestMesh;
	std::vector<std::shared_ptr<tkl::Mesh>> mMeshList;
};

#endif