#include "GameManager.h"

#include "../01_Engine/Mesh.h"
#include "../01_Engine/Camera/FixedCamera.h"
#include "../01_Engine/Camera/PostureControlCamera.h"

//************************************************
// デバッグ用
#include <iostream>
#include "../01_Engine/TestFont.h"
#include "../01_Engine/ResourceManager.h"
#include "../01_Engine/Intersect.h"
#include "../02_Library/Math.h"
#include "../02_Library/Input.h"
std::shared_ptr<Mesh> gCube = nullptr;
std::shared_ptr<Mesh> gPlane = nullptr;
std::shared_ptr<Mesh> gGridGround = nullptr;
tkl::Quaternion gRotation;
//************************************************

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	// 3Dボックス
	gCube = Mesh::CreateBox(50);
 
	// 3D平面
//	gPlane = Mesh::CreatePlane(50);
//	gPlane->SetTexture(ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));

	// グリッド
	gGridGround = Mesh::CreateGround(50, 20);

	// 2D空間用のカメラ作成
	m2DCamera = std::make_shared<FixedCamera>(1024, 768);

	// 3D空間用のカメラ作成
	m3DCamera = std::make_shared<PostureControlCamera>(1024, 768);
#if 1
	m3DCamera->SetPosition(tkl::Vector3(500, 500, 500));
#else
	m3DCamera->SetPosition(tkl::Vector3(0, 150, -300));
#endif
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

//	// TODO：常木講師に確認する
//	tkl::DrawString(0, 0, "aaaaaa", m2DCamera);	// 文字列表示

	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(mousePosX, mousePosY, 1024, 768, m3DCamera->GetView(), m3DCamera->GetProjection());
	tkl::Vector3 hit;
	tkl::Vector3 t = tkl::Vector3::Normalize( m3DCamera->GetTargetPos() - m3DCamera->GetPosition() ) ;

	if(tkl::IsIntersectLinePlane(m3DCamera->GetPosition(), m3DCamera->GetPosition() + (ray * 10000.0f),
		{10, 0, 10}, {0, 1, 0}, &hit))
	{
		gCube->SetPosition(hit);
	}

	gRotation *= tkl::Quaternion::RotationAxis({1, 0, 0}, tkl::ToRadian(1));

//	gPlane->SetRotation(gRotation);
//	gPlane->Draw(m3DCamera);
	
	gCube->SetRotation(gRotation);
	gCube->Draw(m3DCamera);

	gGridGround->Draw(m3DCamera);
}