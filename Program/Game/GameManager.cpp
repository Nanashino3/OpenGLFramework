#include "GameManager.h"
#include "Actor.h"
#include "Component/MeshComponent.h"
#include "Mesh.h"
#include "../Library/Math.h"

//デバッグ用
Actor* gActor = nullptr;

GameManager* GameManager::sInstance = nullptr;
GameManager::GameManager()
{
	gActor = new Actor();
	gActor->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	Quaternion q = Quaternion::RotationAxis(Vector3::UNITY, tkl::ToRadian(90.0f));
	gActor->SetRotation(q);
	gActor->SetScale(Vector3(1.0f, 1.0f, 1.0f));

	MeshComponent* mc = new MeshComponent(gActor);
	mc->SetMesh(Mesh::CreateSphere(1.0f, 16, 8));
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
	gActor->Update();
}