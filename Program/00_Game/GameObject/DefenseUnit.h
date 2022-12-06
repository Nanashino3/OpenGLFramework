// –h‰qƒ†ƒjƒbƒg
#ifndef _DEFENSEUNIT_H_
#define _DEFENSEUNIT_H_

#include <memory>
#include <list>

class Bullet;
class BulletManager;
class AdvanceUnitManager;

namespace tkl{
class Mesh;
class Camera;
class Vector3;
}

class DefenseUnit
{
public:
	DefenseUnit(const tkl::Vector3& pos);
	~DefenseUnit();

	void Update(float deltaTime, std::shared_ptr<tkl::Camera> camera);

private:
	float mElapsed;
	BulletManager* mBulletManager;
	AdvanceUnitManager* mAdvanceManager;
	std::shared_ptr<tkl::Mesh> mMesh;
	std::list<std::shared_ptr<Bullet>> mBullets;
};

#endif