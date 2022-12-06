#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

#include <memory>
#include <list>

class Bullet;
namespace tkl{
class Camera;
class Vector3;
}

class BulletManager
{
public:
	static BulletManager* GetInstance();
	static void DestroyInstance();

	void Create(const tkl::Vector3& pos, float radian);
	void Update(float deltaTime, std::shared_ptr<tkl::Camera> camera);
	bool IsAlive(const tkl::Vector3& pos);

private:
	BulletManager();
	~BulletManager();

private:
	static BulletManager* sMyInstance;
	std::list<std::shared_ptr<Bullet>> mList;
};

#endif