#include "GameManager.h"

#include "../01_Engine/Mesh.h"
#include "../01_Engine/Camera.h"

//************************************************
// デバッグ用
#include <iostream>
#include "../01_Engine/TestFont.h"
Mesh* gBox = nullptr;
Mesh* gGridGround = nullptr;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	tkl::DrawString("あえいうえおあお");

	// ボックス
	gBox = Mesh::CreateBox(50);

	// グリッド
	gGridGround = Mesh::CreateGround(50, 20);

	// カメラの作成
	mCamera = new Camera(1024, 768);
	mCamera->SetPosition(tkl::Vector3(500, 500, 500));
}

GameManager::~GameManager()
{
	delete gBox;
	delete gGridGround;
	delete mCamera;
}

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
	// カメラ更新
	mCamera->Update();

	// オブジェクトの描画
	gBox->Draw(mCamera);
	gGridGround->Draw(mCamera);
}