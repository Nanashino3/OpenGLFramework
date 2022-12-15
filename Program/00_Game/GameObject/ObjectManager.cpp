//****************************************************************************
// ファイル名：ObjectManager(オブジェクト管理者)
// 作　成　日：2022/12/8
#include "ObjectManager.h"
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

//****************************************************************************
// 関数名：Collision
// 概　要：衝突判定(オブジェクト)
// 引　数：なし
// 戻り値：なし
// 詳　細：マップに登録済のオブジェクトリストに対して衝突判定を行う
//****************************************************************************
void ObjectManager::Collision()
{
	for (auto map : mListMap) {
		auto list = &mListMap[map.first];
		for (auto it = list->begin(); it != list->end(); ++it) {
			(*it)->Collision();
		}
	}
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理(オブジェクト)
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：マップに登録済のオブジェクトリストに対して更新処理を行う
//****************************************************************************
void ObjectManager::Update()
{
	for(auto map : mListMap){
		auto list = &mListMap[map.first];
		for(auto it = list->begin(); it != list->end();){
			(*it)->Update();
			if (!(*it)->IsAlive()){ it = list->erase(it); continue; }
			++it;
		}
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理(オブジェクト)
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：マップに登録済のオブジェクトリストに対して描画処理を行う
//****************************************************************************
void ObjectManager::Draw()
{
	for (auto map : mListMap) {
		auto list = &mListMap[map.first];
		for (auto it = list->begin(); it != list->end(); ++it) {
			(*it)->Draw();
		}
	}
}