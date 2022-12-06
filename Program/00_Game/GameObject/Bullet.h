#ifndef _BULLET_H_
#define _BULLET_H_

#include <memory>
#include "../../02_Library/Vector.h"

namespace tkl {
class Mesh;
class Camera;
}

class Bullet
{
public:
	Bullet(const tkl::Vector3& pos, float radian);
	~Bullet();

	void Update(float deltaTime, std::shared_ptr<tkl::Camera> camera);
	bool IsAlive() const { return mIsAlive; }
	tkl::Vector3 GetLauncherPos() const { return mLauncherPos; }

private:
	float mRadian;
	bool mIsAlive;
	tkl::Vector3 mLauncherPos;
	std::shared_ptr<tkl::Mesh> mMesh;
};

#endif