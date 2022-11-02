#include "GameMain.h"
#include "../01_Engine/GameManager.h"

void GameMain(float deltaTime)
{
	tkl::GameManager* manager = tkl::GameManager::GetInstance();
	manager->Update(deltaTime);
}

void GameEnd()
{
	tkl::GameManager* manager = tkl::GameManager::GetInstance();
	manager->DestoryInstance();
}