#include "GameManager.h"

#include "../01_Engine/Mesh.h"
#include "../01_Engine/Camera/FixedCamera.h"
#include "../01_Engine/Camera/PostureControlCamera.h"

//************************************************
// デバッグ用
#include <iostream>
#include "../01_Engine/TestFont.h"
#include "../01_Engine/ResourceManager.h"
std::shared_ptr<Mesh> gPlane = nullptr;
std::shared_ptr<Mesh> gGridGround = nullptr;
std::shared_ptr<Mesh> gTexture = nullptr;
int gImageHdl = 0;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
//	gTexture = Mesh::CreatePlaneForTexture();
//	gTexture->SetTexture(ResourceManager::GetInstance()->CreateTextureFromFile("Resource/Ship.png"));

	// 3D平面
	gPlane = Mesh::CreatePlane(50);
	gPlane->SetTexture(ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));

	// グリッド
	gGridGround = Mesh::CreateGround(50, 20);

	// 2D空間用のカメラ作成
	m2DCamera = std::make_shared<FixedCamera>(1024, 768);

	// 3D空間用のカメラ作成
	m3DCamera = std::make_shared<PostureControlCamera>(1024, 768);
	m3DCamera->SetPosition(tkl::Vector3(500, 500, 500));
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
	m2DCamera->Update();
	m3DCamera->Update();

	// TODO：常木講師に確認する
	tkl::DrawString(100, 100, "あえいうえおあお", m2DCamera);	// 文字列表示

	// オブジェクトの描画
//	gTexture->Draw(m2DCamera);
	gPlane->Draw(m3DCamera);
	gGridGround->Draw(m3DCamera);
}