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
	
	// 終点(目標)-始点(発射元)のベクトル
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

	// 進む方向計算
	pos.mX += cosf(mRadian) * 50.0f * param->GetDeltaTime();
	pos.mZ += sinf(mRadian) * 50.0f * param->GetDeltaTime();

	mMesh->SetPosition(pos);
	mMesh->Draw(param->GetCamera());

	// 一定距離まで行ったら弾削除
	float d = tkl::Vector3::Distance(mLauncherPos, pos);
	if (d > DESTROY_POS) { mIsAlive = false; }
}