#include "ObjectManager.h"

#include "Bullet.h"
#include "AdvanceUnit.h"
#include "DefenseUnit.h"
#include "GameParameter.h"

ObjectManager* ObjectManager::sMyInstance = nullptr;
ObjectManager::ObjectManager()
{
	mListMap[typeid(Bullet).name()] = &mBulletList;
	mListMap[typeid(AdvanceUnit).name()] = &mAdvanceList;
	mListMap[typeid(DefenseUnit).name()] = &mDefenseList;
}

ObjectManager::~ObjectManager()
{}

ObjectManager* ObjectManager::GetInstance()
{
	if(!sMyInstance) sMyInstance = new ObjectManager;
	return sMyInstance;
}
void ObjectManager::DestroyInstance()
{
	delete sMyInstance;
}

void ObjectManager::Update(std::shared_ptr<GameParameter> param)
{
	for(auto it = mAdvanceList.begin(); it != mAdvanceList.end();){
		(*it)->Update(param);
		if(!(*it)->IsAlive()) { it = mAdvanceList.erase(it); continue; }
		++it;
	}

	for(auto it = mDefenseList.begin(); it != mDefenseList.end(); ++it){
		(*it)->Update(param);
	}

	for(auto it = mBulletList.begin(); it != mBulletList.end();){
		(*it)->Update(param);
		if(!(*it)->IsAlive()){ it = mBulletList.erase(it); continue; }
		++it;
	}
}