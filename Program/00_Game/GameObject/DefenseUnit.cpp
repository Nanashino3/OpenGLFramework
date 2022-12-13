//****************************************************************************
// ファイル名：DefenseUnit(防衛ユニットクラス)
// 作　成　日：2022/12/5
#include "DefenseUnit.h"

#include "Bullet.h"
#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

DefenseUnit::DefenseUnit(std::shared_ptr<GameParameter> param)
: mMesh(nullptr)
{
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_water.bmp"));

	tkl::Vector3 clickPos = param->GetClickPos();
	mMesh->SetPosition(tkl::Vector3(clickPos.mX, 12.5f, clickPos.mZ));
}

DefenseUnit::~DefenseUnit()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：防衛ユニットクラスの更新処理
//****************************************************************************
void DefenseUnit::Update(std::shared_ptr<GameParameter>& param)
{
	// 自身(防衛ユニット)を描画
	mMesh->Draw(param->GetCamera());
	
	// 生存していない場合は弾生成
	if (!mBullet.expired()) { return; }
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	if (list.size() != 0) {
		tkl::Vector3 nearPos;
		for (auto it = list.begin(); it != list.end(); ++it) {
			std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);
			tkl::Vector3 pos = unit->GetUnitPosition();
			float distance = tkl::Vector3::Distance(pos, mMesh->GetPosition());
			if (distance <= 55.0f) { nearPos = pos; break; }
		}
		if (tkl::Vector3::Magnitude(nearPos) == 0) { return; }

		// 弾関連処理
		mBullet = ObjectManager::GetInstance()->Create<Bullet>(param);
		std::shared_ptr<Bullet> bullet = mBullet.lock();
		bullet->SetLauncherPos(mMesh->GetPosition());
		bullet->SetTargetPos(nearPos);
		bullet->Preparation();
	}
}