#include "GameManager.h"

#include "../01_Engine/Mesh.h"
#include "../01_Engine/Camera/FixedCamera.h"
#include "../01_Engine/Camera/PostureControlCamera.h"

//************************************************
// �f�o�b�O�p
#include <iostream>
#include "../01_Engine/ResourceManager.h"
std::shared_ptr<Mesh> gPlane = nullptr;
std::shared_ptr<Mesh> gGridGround = nullptr;
std::shared_ptr<Mesh> gTexture = nullptr;
int gImageHdl = 0;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	// TODO�F��؍u�t�Ɋm�F����
//	tkl::DrawString(100, 100, "����������������");	// ������\��

//	gImageHdl = ResourceManager::GetInstance()->GetTextureHandle("Resource/Ship.png");

	gTexture = Mesh::CreatePlaneForTexture();
	gTexture->SetTexture(ResourceManager::GetInstance()->CreateTextureFromFile("Resource/Ship.png"));

	// 3D����
	gPlane = Mesh::CreatePlane(50);
	gPlane->SetTexture(ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));

	// �O���b�h
	gGridGround = Mesh::CreateGround(50, 20);

	// 2D��ԗp�̃J�����쐬
	m2DCamera = std::make_shared<FixedCamera>(1024, 768);

	// 3D��ԗp�̃J�����쐬
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
	// �J�����X�V
	m2DCamera->Update();
	m3DCamera->Update();

//	ResourceManager::GetInstance()->DrawGraph(100, 100, gImageHdl, 0);

	// �I�u�W�F�N�g�̕`��
	gTexture->Draw(m2DCamera);
	gPlane->Draw(m3DCamera);
	gGridGround->Draw(m3DCamera);
}