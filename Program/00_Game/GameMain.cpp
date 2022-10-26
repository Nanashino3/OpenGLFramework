#include "GameMain.h"
#include "../01_Engine/GameManager.h"

void GameMain(float deltaTime)
{
	GameManager* manager = GameManager::GetInstance();
	manager->Update(deltaTime);
}

void GameEnd()
{
	GameManager* manager = GameManager::GetInstance();
	manager->DestoryInstance();
}