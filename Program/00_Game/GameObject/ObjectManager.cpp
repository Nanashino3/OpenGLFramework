#include "ObjectManager.h"

#include "GameObject.h"
#include "GameParameter.h"

ObjectManager* ObjectManager::sMyInstance = nullptr;
ObjectManager::ObjectManager()
{}

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

void ObjectManager::Update(std::shared_ptr<GameParameter>& param)
{
	for(auto map : mListMap){
		auto list = &mListMap[map.first];
		for(auto it = list->begin(); it != list->end();){
			(*it)->Update(param);
			if (!(*it)->IsAlive()){ it = list->erase(it); continue; }
			++it;
		}
	}
}