#include "GameManager.h"
//#include "Actor.h"

//デバッグ用
//Actor* gActor = nullptr;

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
//	gActor = new Actor();
//	gActor->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
//	gActor->SetScale(Vector3(1.0f, 1.0f, 1.0f));
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

}