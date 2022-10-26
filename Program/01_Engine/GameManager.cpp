#include "GameManager.h"

#include "../01_Engine/Mesh.h"
#include "../01_Engine/Camera/PostureControlCamera.h"

//************************************************
// �f�o�b�O�p
#include <iostream>
#include "../01_Engine/ResourceManager.h"
Mesh* gPlane = nullptr;
Mesh* gGridGround = nullptr;
int gImageHdl = 0;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	// TODO�F��؍u�t�Ɋm�F����
//	tkl::DrawString(100, 100, "����������������");	// ������\��

	gImageHdl = ResourceManager::GetInstance()->GetTextureHandle("Resource/Ship.png");

	// 3D����
	gPlane = Mesh::CreatePlane(50);
	gPlane->SetTexture(ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));

	// �O���b�h
	gGridGround = Mesh::CreateGround(50, 20);

	// �J�����̍쐬
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
	// �J�����X�V
	mCamera->Update();

	ResourceManager::GetInstance()->DrawGraph(100, 100, gImageHdl, 0);

	// �I�u�W�F�N�g�̕`��
	gPlane->Draw(mCamera);
	gGridGround->Draw(mCamera);
}