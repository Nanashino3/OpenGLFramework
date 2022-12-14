//****************************************************************************
// ファイル名：ObjectManager(オブジェクト管理者)
// 作　成　日：2022/12/8
#include "ObjectManager.h"
#include "GameObject.h"
#include "GameParameter.h"
#include "../../02_Library/Utility.h"

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
	TKL_SAFE_DELETE(sMyInstance) ;
}

void ObjectManager::Collision()
{
	for (auto map : mListMap) {
		auto list = &mListMap[map.first];
		for (auto it = list->begin(); it != list->end(); ++it) {
			(*it)->Collision();
		}
	}
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

void ObjectManager::Draw(std::shared_ptr<GameParameter>& param)
{
	for (auto map : mListMap) {
		auto list = &mListMap[map.first];
		for (auto it = list->begin(); it != list->end(); ++it) {
			(*it)->Draw(param);
		}
	}
}