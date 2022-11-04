#include "GameManager.h"

#include "Scene/BaseScene.h"
#include "Scene/TitleScene.h"

#include "../01_Engine/Font.h"

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	mScene = std::make_shared<TitleScene>();
}

GameManager::~GameManager()
{}

GameManager* GameManager::GetInstance()
{
	if(!sInstance){
		sInstance = new GameManager();
	}
	return sInstance;
}
void GameManager::DestoryInstance()
{
	delete sInstance;
}

void GameManager::Update(float deltaTime)
{
	std::shared_ptr<BaseScene> nextScene = mScene->Update();
	if(mScene != nextScene){
		mScene = nextScene;
		nextScene = nullptr;
	}
}