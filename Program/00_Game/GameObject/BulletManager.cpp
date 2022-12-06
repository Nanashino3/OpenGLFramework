#include "BulletManager.h"

#include "Bullet.h"

BulletManager* BulletManager::sMyInstance = nullptr;
BulletManager::BulletManager()
{}

BulletManager::~BulletManager()
{}

BulletManager* BulletManager::GetInstance()
{
	if(!sMyInstance) sMyInstance = new BulletManager;
	return sMyInstance;
}

void BulletManager::DestroyInstance()
{
	delete sMyInstance;
}

void BulletManager::Create(const tkl::Vector3& pos, float radian)
{
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(pos, radian);
	mList.emplace_back(bullet);
}

void BulletManager::Update(float deltaTime, std::shared_ptr<tkl::Camera> camera)
{
	for (auto iter = mList.begin(); iter != mList.end();) {
		(*iter)->Update(deltaTime, camera);
		if(!(*iter)->IsAlive()){ iter = mList.erase(iter); continue; }
		++iter;
	}
}

bool BulletManager::IsAlive(const tkl::Vector3& pos)
{
	for (auto iter = mList.begin(); iter != mList.end(); ++iter) {
		if(pos == (*iter)->GetLauncherPos()){ return true; }
	}
	return false;
}