#include "GameManager.h"

#include "Scene/TitleScene.h"
#include "Scene/SceneManager.h"

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	mSceneManager = std::make_shared<SceneManager>();
	mSceneManager->LoadScene<TitleScene>();
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
	mSceneManager->SceneUpdate(deltaTime);
}