#ifndef _BULLET_H_
#define _BULLET_H_

#include <memory>
#include "GameObject.h"
#include "../../02_Library/Vector.h"

namespace tkl { class Mesh; }
class Bullet : public GameObject
{
public:
	Bullet(std::shared_ptr<GameParameter> param);
	virtual ~Bullet();

	virtual void Update(std::shared_ptr<GameParameter> param) final;
	virtual bool IsAlive() final { return mIsAlive; }
	tkl::Vector3 GetLauncherPos() const { return mLauncherPos; }

private:
	float mRadian;
	bool mIsAlive;
	tkl::Vector3 mLauncherPos;
	tkl::Vector3 mDiffPos;
	std::shared_ptr<tkl::Mesh> mMesh;
};

#endif