//****************************************************************************
// ファイル名：GameManager(ゲーム管理者クラス)
// 作　成　日：2022/10/6
#include "GameManager.h"

#include "Scene/TitleScene.h"
#include "Scene/SceneManager.h"
#include "../02_Library/Utility.h"

GameManager* GameManager::sMyInstance = nullptr;
GameManager::GameManager()
{
	SceneManager::GetInstance()->LoadScene(std::make_shared<TitleScene>());
}

GameManager::~GameManager()
{
	SceneManager::DestoryInstance();
}

GameManager* GameManager::GetInstance()
{
	if(!sMyInstance){ sMyInstance = new GameManager(); }
	return sMyInstance;
}
void GameManager::DestoryInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void GameManager::Update(float deltaTime)
{
	SceneManager::GetInstance()->SceneUpdate(deltaTime);
}