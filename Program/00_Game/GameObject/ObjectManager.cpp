#include "ObjectManager.h"

#include "Bullet.h"
#include "AdvanceUnit.h"
#include "DefenseUnit.h"
#include "GameParameter.h"

ObjectManager* ObjectManager::sMyInstance = nullptr;
ObjectManager::ObjectManager()
{
	mListMap[typeid(AdvanceUnit).name()] = &mAdvanceList;
	mListMap[typeid(DefenseUnit).name()] = &mDefenseList;
	mListMap[typeid(Bullet).name()] = &mBulletList;
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
	for(auto map : mListMap){
		auto list = map.second;
		if(list->empty()) continue;
		
		for(auto it = list->begin(); it != list->end();){
			(*it)->Update(param);
			if (!(*it)->IsAlive()) { it = list->erase(it); continue; }
			++it;
		}
	}
}