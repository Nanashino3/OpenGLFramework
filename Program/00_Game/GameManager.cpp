#include "GameManager.h"

#include "Scene/TitleScene.h"
#include "Scene/SceneManager.h"
#include "../02_Library/Utility.h"

GameManager* GameManager::sMyInstance = nullptr;
GameManager::GameManager()
{
	mSceneManager = std::make_shared<SceneManager>();
	mSceneManager->LoadScene<TitleScene>();
}

GameManager::~GameManager()
{}

GameManager* GameManager::GetInstance()
{
	if(!sMyInstance) sMyInstance = new GameManager();
	return sMyInstance;
}
void GameManager::DestoryInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

void GameManager::Update(float deltaTime)
{
	mSceneManager->SceneUpdate(deltaTime);
}