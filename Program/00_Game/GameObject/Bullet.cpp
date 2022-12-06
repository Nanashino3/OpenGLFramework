#include "Bullet.h"

#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

Bullet::Bullet(const tkl::Vector3& pos, float radian)
: mRadian(radian)
, mIsAlive(true)
, mMesh(nullptr)
, mLauncherPos(pos)
{
	mMesh = tkl::Mesh::CreateSphere(5, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
	mMesh->SetPosition(pos);
}

Bullet::~Bullet()
{}

void Bullet::Update(float deltaTime, std::shared_ptr<tkl::Camera> camera)
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// 進む方向計算
	pos.mX += sinf(mRadian) * 25.0f * deltaTime;
	pos.mZ += cosf(mRadian) * 25.0f * deltaTime;

	// 一定距離まで行ったら弾削除
	float magnitude = tkl::Vector3::Distance(pos, mLauncherPos);
	if(magnitude > 55.0f){ mIsAlive = false; }

	mMesh->SetPosition(pos);
	mMesh->Draw(camera);
}