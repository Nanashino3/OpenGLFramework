//****************************************************************************
// ファイル名：ObjectManager(オブジェクト管理者)
// 作　成　日：2022/12/8
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

//****************************************************************************
// 関数名：Update
// 概　要：更新処理(オブジェクト)
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：マップに登録済のオブジェクトリストに対して更新処理をかける
//****************************************************************************
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