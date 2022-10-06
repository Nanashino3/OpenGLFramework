#include "GameMain.h"
#include "GameManager.h"

void GameMain(float deltaTime)
{
	GameManager* manager = GameManager::GetInstance();
	manager->Update(deltaTime);
}