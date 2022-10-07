#include "GameManager.h"

#include "Mesh.h"
#include "Camera.h"
#include "../Library/Math.h"

// デバッグ用
Mesh* gBox = nullptr;

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	// 球体作成
//	gBox = Mesh::CreateSphere(50.0f, 24, 16);
	gBox = Mesh::CreateBox(25.0f, 25.0f, 25.0f);

	// カメラの作成
	mCamera = new Camera(1024, 768);
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
	mCamera->Update();
	gBox->Render(mCamera);
}