#include "Bullet.h"

#include "GameParameter.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

const int BULLET_SIZE = 5;
const float DESTROY_POS = 70.0f;

Bullet::Bullet(std::shared_ptr<GameParameter> param)
: mRadian(0)
, mMesh(nullptr)
, mLauncherPos(tkl::Vector3::ZERO)
, mDiffPos(tkl::Vector3::ZERO)
{
	mLauncherPos = param->GetLauncherPos();
	
	// �I�_(�ڕW)-�n�_(���ˌ�)�̃x�N�g��
	tkl::Vector3 targetPos = param->GetTargetPos();
	mDiffPos = targetPos - mLauncherPos;

	mRadian = atan2f(mDiffPos.mZ, mDiffPos.mX);

	mMesh = tkl::Mesh::CreateSphere(BULLET_SIZE, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
	mMesh->SetPosition(mLauncherPos);
}

Bullet::~Bullet()
{}

void Bullet::Update(std::shared_ptr<GameParameter> param)
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// �i�ޕ����v�Z
	pos.mX += cosf(mRadian) * 50.0f * param->GetDeltaTime();
	pos.mZ += sinf(mRadian) * 50.0f * param->GetDeltaTime();

	mMesh->SetPosition(pos);
	mMesh->Draw(param->GetCamera());

	// ��苗���܂ōs������e�폜
	float d = tkl::Vector3::Distance(mLauncherPos, pos);
	if (d > DESTROY_POS) { mIsAlive = false; }
}