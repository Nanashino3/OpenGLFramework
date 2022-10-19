#include "GameManager.h"

#include "Mesh.h"
#include "Camera.h"
#include "../Library/Math.h"
#include "../Library/Input.h"

// デバッグ用
#include <iostream>
#include "../Library/FontTexture.h"
Mesh* gBox = nullptr;
Mesh* gGridGround = nullptr;

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
//	FontTexture::CreateFontTexture();
	// ボックス
	gBox = Mesh::CreateBox(50, 50, 50);

	// グリッド
	gGridGround = Mesh::CreateGround(100, 20);

	// カメラの作成
	mCamera = new Camera(1024, 768);
#if 1
	mCamera->SetPosition(tkl::Vector3(500, 500, 500));
#else
	mCamera->SetPosition(tkl::Vector3(0, 0, 500));
#endif
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