#include "DefenseUnit.h"

#include "AdvanceUnitManager.h"
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

	mBulletManager = BulletManager::GetInstance();
	mAdvanceManager = AdvanceUnitManager::GetInstance();
}

DefenseUnit::~DefenseUnit()
{}

void DefenseUnit::Update(float deltaTime, std::shared_ptr<tkl::Camera> camera)
{
	mMesh->Draw(camera);

	// 1”Ô‹ß‚¢iŒRƒ†ƒjƒbƒg‚ðŽæ“¾
	tkl::Vector3 nearUnit = mAdvanceManager->GetNearUnit(mMesh->GetPosition());
	if(tkl::Vector3::Magnitude(nearUnit) == 0){ return;	}

	tkl::Vector3 diff = nearUnit - mMesh->GetPosition();
	float radian = atan2f(diff.mX, diff.mZ);

	// ¶‘¶‚µ‚Ä‚¢‚È‚¢ê‡’e¶¬
	if(!mBulletManager->IsAlive(mMesh->GetPosition())){ mBulletManager->Create(mMesh->GetPosition(), radian); }
	// ’eXV
	mBulletManager->Update(deltaTime, camera);

//	mElapsed += deltaTime;
//	if(mElapsed > 2.0f){
//		mElapsed = 0;
//	}
}