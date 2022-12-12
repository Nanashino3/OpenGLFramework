#include "Bullet.h"

#include "GameParameter.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

// TODO�F�萔�͂ǂ����ɂ܂Ƃ߂�H
const int BULLET_SIZE = 5;
const float DESTROY_POS = 70.0f;

Bullet::Bullet(std::shared_ptr<GameParameter> param)
: mRadian(0)
, mMesh(nullptr)
{
	mMesh = tkl::Mesh::CreateSphere(BULLET_SIZE, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
}

Bullet::~Bullet()
{}

void Bullet::Preparation()
{
	tkl::Vector3 diff = mTargetPos - mLauncherPos;
	mRadian = atan2f(diff.mZ, diff.mX);

	mMesh->SetPosition(mLauncherPos);
}

void Bullet::Update(std::shared_ptr<GameParameter> param)
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// �i�ޕ����v�Z
	pos.mX += cosf(mRadian) * 50.0f * param->GetDeltaTime();
	pos.mZ += sinf(mRadian) * 50.0f * param->GetDeltaTime();

	// ��苗���܂ōs������e�폜
	float d = tkl::Vector3::Distance(mLauncherPos, pos);
	if (d > DESTROY_POS) { mIsAlive = false; }

	mMesh->SetPosition(pos);
	mMesh->Draw(param->GetCamera());
}