#include "GameManager.h"

#include "../01_Engine/Mesh.h"
#include "../01_Engine/Camera/PostureControlCamera.h"

//************************************************
// デバッグ用
#include <iostream>
#include "../01_Engine/ResourceManager.h"
Mesh* gPlane = nullptr;
Mesh* gGridGround = nullptr;
int gImageHdl = 0;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	// TODO：常木講師に確認する
//	tkl::DrawString(100, 100, "あえいうえおあお");	// 文字列表示

	gImageHdl = ResourceManager::GetInstance()->GetTextureHandle("Resource/Ship.png");

	// 3D平面
	gPlane = Mesh::CreatePlane(50);
	gPlane->SetTexture(ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));

	// グリッド
	gGridGround = Mesh::CreateGround(50, 20);

	// カメラの作成
	mCamera = std::make_unique<PostureControlCamera>(1024, 768);
	mCamera->SetPosition(tkl::Vector3(500, 500, 500));
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
	// カメラ更新
	mCamera->Update();

	ResourceManager::GetInstance()->DrawGraph(100, 100, gImageHdl, 0);

	// オブジェクトの描画
	gPlane->Draw(mCamera);
	gGridGround->Draw(mCamera);
}