#include "GameManager.h"

#include "Mesh.h"
#include "Camera.h"
#include "Renderer.h"
#include "../Library/Math.h"
#include "../Library/Input.h"

#include "MeshComponent.h"
#include "WireComponent.h"

// デバッグ用
Mesh* gBox = nullptr;
Mesh* gGridGround = nullptr;

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
: mRenderer(nullptr)
{
	// 描画クラス
	mRenderer = new Renderer();
	mRenderer->Initialize();

	// ボックス
	gBox = Mesh::CreateBox(50, 50, 50);
	MeshComponent* mc = new MeshComponent();
	mc->SetMesh(gBox);
	mRenderer->AddMeshComponent(mc);

	// グリッド
	gGridGround = Mesh::CreateGround(100, 20);
	WireComponent* wc = new WireComponent();
	wc->SetMesh(gGridGround);
	mRenderer->AddWireComponent(wc);

	// カメラの作成
	mCamera = new Camera(1024, 768);
	mCamera->SetPosition(Vector3(500, 500, 500));
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
	Vector3 pos = gBox->GetPosition();
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

	gBox->SetPosition(pos);
	mCamera->Update();
	mRenderer->Draw(mCamera);
}