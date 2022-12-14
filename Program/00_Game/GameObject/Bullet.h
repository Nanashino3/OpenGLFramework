#ifndef _BULLET_H_
#define _BULLET_H_

#include <memory>
#include "GameObject.h"
//#include "../../02_Library/Vector.h"

namespace tkl {
class Mesh;
}

class Bullet : public GameObject
{
public:
	Bullet(std::shared_ptr<GameParameter> param);
	virtual ~Bullet();

	void Preparation();
	virtual void Collision() final;
	virtual void Update(std::shared_ptr<GameParameter>& param) final;
	virtual void Draw(std::shared_ptr<GameParameter>& param) final;
	void SetLauncherPos(const tkl::Vector3& pos){ mLauncherPos = pos; }
	void SetTargetPos(const tkl::Vector3& pos){ mTargetPos = pos; }

private:
	float mRadian;
	tkl::Vector3 mTargetPos;
	tkl::Vector3 mLauncherPos;
	std::shared_ptr<tkl::Mesh> mMesh;
};

#endif