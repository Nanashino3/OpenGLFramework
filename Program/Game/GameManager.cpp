#include "GameManager.h"

#include "Mesh.h"
#include "Camera.h"
#include "../Library/Math.h"
#include "../Library/Input.h"

// デバッグ用
#include <iostream>
Mesh* gBox = nullptr;
Mesh* gGridGround = nullptr;

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	// ボックス
	gBox = Mesh::CreateBox(50, 50, 50);

	// グリッド
	gGridGround = Mesh::CreateGround(100, 20);

	// カメラの作成
	mCamera = new Camera(1024, 768);
	mCamera->SetPosition(Vector3(500, 500, 500));
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
	Vector3 pos = gBox->GetPosition();
	Quaternion camRot = mCamera->GetRotation();
	if(tkl::Input::IsKeyDown(eKeys::KB_D)){
		pos.mX += 1.0f;
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_A)){
		pos.mX -= 1.0f;
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_W)){
		pos.mZ -= 1.0f;
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_S)){
		pos.mZ += 1.0f;
	}

#if 0
	if(tkl::Input::IsKeyDown(eKeys::KB_LEFT)){
		camRot *= Quaternion::RotationAxis(mCamera->Up(), tkl::ToRadian(1));
	}
	if(tkl::Input::IsKeyDown(eKeys::KB_RIGHT)){
		camRot *= Quaternion::RotationAxis(mCamera->Up(), tkl::ToRadian(-1));
	}
#else
	if(tkl::Input::IsMouseInput(eMouse::MOUSE_INPUT_LEFT)){
		camRot *= Quaternion::RotationAxis(mCamera->Up(), tkl::ToRadian(1));
	}
	if(tkl::Input::IsMouseInput(eMouse::MOUSE_INPUT_RIGHT)){
		camRot *= Quaternion::RotationAxis(mCamera->Up(), tkl::ToRadian(-1));
	}
#endif
	gBox->SetPosition(pos);
	mCamera->SetRotation(camRot);
	mCamera->Update();

	gBox->Draw(mCamera);
	gGridGround->Draw(mCamera);
}