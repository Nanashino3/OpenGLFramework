#include "GameManager.h"

#include "Mesh.h"
#include "Camera.h"
#include "../Library/Math.h"
#include "../Library/Input.h"

// �f�o�b�O�p
#include <iostream>
#include "../Library/FontTexture.h"
Mesh* gBox = nullptr;
Mesh* gSphere = nullptr;
Mesh* gGridGround = nullptr;

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
//	FontTexture::CreateFontTexture();
	// �{�b�N�X
	gBox = Mesh::CreateBox(50, 50, 50);

	gSphere = Mesh::CreateSphere(50, 24, 16);

	// �O���b�h
//	gGridGround = Mesh::CreateGround(100, 20);

	// �J�����̍쐬
	mCamera = new Camera(1024, 768);
#if 1
	mCamera->SetPosition(Vector3(500, 500, 500));
#else
	mCamera->SetPosition(Vector3(0, 0, 500));
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
	// �J�����X�V
	mCamera->Update();

	// �I�u�W�F�N�g�̕`��
	gBox->Draw(mCamera);
	gSphere->Draw(mCamera);
//	gGridGround->Draw(mCamera);
}