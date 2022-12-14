//****************************************************************************
// ファイル名：Bullet(弾クラス)
// 作　成　日：2022/12/6
#include "Bullet.h"

#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"

// TODO：定数はどこかにまとめる？
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

//****************************************************************************
// 関数名：Preparation
// 概　要：事前準備
// 引　数：なし
// 戻り値：なし
// 詳　細：弾クラスの事前準備を行う
//****************************************************************************
void Bullet::Preparation()
{
	tkl::Vector3 diff = mTargetPos - mLauncherPos;
	mRadian = atan2f(diff.mZ, diff.mX);

	mMesh->SetPosition(mLauncherPos);
}

//****************************************************************************
// 関数名：Collision
// 概　要：衝突判定
// 引　数：
// 戻り値：
// 詳　細：弾クラスの衝突判定
//****************************************************************************
void Bullet::Collision()
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// 進軍ユニットリストを取得
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	for(auto it = list->begin(); it != list->end(); ++it){
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);		
		tkl::Vector3 unitPos = unit->GetUnitPosition();

		// 進軍ユニットと衝突していたら弾削除
		if(tkl::IsIntersectAABB(pos, 12.5f, unitPos, 5.0f)){
			mIsAlive = false;
			// TODO：与えるダメージは可変にしたい
			unit->ReceiveDamage(10);
			break; 
		}
	}
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：弾クラスの更新処理
//****************************************************************************
void Bullet::Update(std::shared_ptr<GameParameter>& param)
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// 進む方向計算
	pos.mX += cosf(mRadian) * 50.0f * param->GetDeltaTime();
	pos.mZ += sinf(mRadian) * 50.0f * param->GetDeltaTime();

	// 一定距離まで行ったら弾削除
	float d = tkl::Vector3::Distance(mLauncherPos, pos);
	if (d > DESTROY_POS) { mIsAlive = false; }

	mMesh->SetPosition(pos);
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：弾クラスの描画処理
//****************************************************************************
void Bullet::Draw(std::shared_ptr<GameParameter>& param)
{
	mMesh->Draw(param->GetCamera());
}