#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

void SceneManager::ReturnScene()
{
	if(mSceneList.empty()) return ;
	mSceneList.pop();
	mScene = mSceneList.top();
}

void SceneManager::SceneUpdate(float deltaTime)
{
	mScene->Update(deltaTime);
	mScene->Draw();
}