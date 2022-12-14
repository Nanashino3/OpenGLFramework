#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

void SceneManager::SceneUpdate(float deltaTime)
{
	mScene->Update(deltaTime);
	mScene->Draw();
}