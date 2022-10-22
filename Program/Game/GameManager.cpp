#include "GameManager.h"

#include "Mesh.h"
#include "Camera.h"

//************************************************
// �f�o�b�O�p
#include <iostream>
//#include "../Library/Utility.h"
//#include "../Library/FontTexture.h"
Mesh* gBox = nullptr;
Mesh* gGridGround = nullptr;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
//	auto temp = tnl::CreateFontTexture(32, tkl::ToOnceWChara("��"));

	// �{�b�N�X
	gBox = Mesh::CreateBox(50);

	// �O���b�h
	gGridGround = Mesh::CreateGround(50, 20);

	// �J�����̍쐬
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
	// �J�����X�V
	mCamera->Update();

	// �I�u�W�F�N�g�̕`��
	gBox->Draw(mCamera);
	gGridGround->Draw(mCamera);
}