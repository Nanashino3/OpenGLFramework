#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

void SceneManager::ReturnScene()
{
	if(mPrevScene.empty()) return ;
	mNextScene = mPrevScene.top();
	mPrevScene.pop();
}

void SceneManager::SceneUpdate(float deltaTime)
{
	// シーンのインスタンスを更新
	if(mNowScene != mNextScene){ mNowScene = mNextScene; }

	// 現在のシーンの処理
	mNowScene->Update(deltaTime);
	mNowScene->Draw();

	if(mPrevScene.empty()){ return; }
	
	auto prevScene = mPrevScene.top();
	prevScene->Draw();
}