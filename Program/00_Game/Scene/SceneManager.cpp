//****************************************************************************
// ファイル名：SceneManager(画面管理クラス)
// 作　成　日：2022/12/15
#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

//****************************************************************************
// 関数名：ReturnScene
// 概　要：画面を戻す
// 引　数：なし
// 戻り値：なし
// 詳　細：遷移前の画面に戻る
//****************************************************************************
void SceneManager::ReturnScene()
{
	if(mPrevScene.empty()){ return; }
	mNextScene = mPrevScene.top();
	mPrevScene.pop();
}

//****************************************************************************
// 関数名：SceneUpdate
// 概　要：画面の更新
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：画面の更新を行う
//****************************************************************************
void SceneManager::SceneUpdate(float deltaTime)
{
	// シーンのインスタンスを更新
	if(mNowScene != mNextScene){ mNowScene = mNextScene; }

	if(!mPrevScene.empty()){
		auto prevScene = mPrevScene.top();
		prevScene->Draw();
	}

	// 現在のシーンの処理
	mNowScene->Update(deltaTime);
	mNowScene->Draw();
}