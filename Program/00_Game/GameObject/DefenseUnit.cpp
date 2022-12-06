#include "DefenseUnit.h"

#include "BulletManager.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

DefenseUnit::DefenseUnit(const tkl::Vector3& pos)
: mElapsed(0)
, mMesh(nullptr)
{
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_water.bmp"));
	mMesh->SetPosition(tkl::Vector3(pos.mX, 12.5f, pos.mZ));
}

DefenseUnit::~DefenseUnit()
{}

void DefenseUnit::Update(float deltaTime, std::shared_ptr<tkl::Camera> camera)
{
	mElapsed += deltaTime;
	if(mElapsed > 2.0f){
		mElapsed = 0;

		// ’e¶¬
		BulletManager::GetInstance()->Create(mMesh->GetPosition());
	}
	// ’eXV
	BulletManager::GetInstance()->Update(deltaTime, camera);

	mMesh->Draw(camera);
}