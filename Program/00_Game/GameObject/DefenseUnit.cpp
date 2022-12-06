#include "DefenseUnit.h"

#include "Bullet.h"
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

		// íeê∂ê¨
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(mMesh->GetPosition());
		mBullets.emplace_back(bullet);
	}

	// íeçXêV
	for(auto iter = mBullets.begin(); iter != mBullets.end(); ++iter){
		(*iter)->Update(deltaTime, camera);
	}

	mMesh->Draw(camera);
}