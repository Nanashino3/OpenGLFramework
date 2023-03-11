#include "GameMain.h"
#include "../00_Game/GameManager.h"

void GameMain(float deltaTime)
{
	GameManager::GetInstance()->Update(deltaTime);
}

void GameEnd()
{
	GameManager::DestoryInstance();
}