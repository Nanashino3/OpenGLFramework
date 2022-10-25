#include "GameManager.h"

#include "../01_Engine/Mesh.h"
#include "../01_Engine/Camera.h"

//************************************************
// デバッグ用
#include <iostream>
#include "../01_Engine/Texture.h"
Mesh* gPlane = nullptr;
Mesh* gGridGround = nullptr;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	// TODO：常木講師に確認する
//	tkl::DrawString(100, 100, "あえいうえおあお");



	// 3D平面
	gPlane = Mesh::CreatePlane(50);
	gPlane->SetTexture(Texture::CreateTextureFromFile("Resource/Ship.png"));

	// グリッド
	gGridGround = Mesh::CreateGround(50, 20);

	// カメラの作成
	mCamera = new Camera(1024, 768);
	mCamera->SetPosition(tkl::Vector3(500, 500, 500));
}

GameManager::~GameManager()
{
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
	gPlane->Draw(mCamera);
	gGridGround->Draw(mCamera);
}