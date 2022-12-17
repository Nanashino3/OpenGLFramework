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

DefenseUnit::DefenseUnit(std::shared_ptr<Parameter> param)
: mMesh(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
}

DefenseUnit::~DefenseUnit()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：防衛ユニットクラスの初期化処理
//****************************************************************************
void DefenseUnit::Initialize()
{
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_water.bmp"));

	tkl::Vector3 clickPos = mParam->GetClickPos();
	mMesh->SetPosition(tkl::Vector3(clickPos.mX, 12.5f, clickPos.mZ));

	mParam->SetTotalCost(mParam->GetTotalCost() - CONSUME_COST);
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：防衛ユニットクラスの更新処理
//****************************************************************************
void DefenseUnit::Update()
{
	if (!mBullet.expired()) { return; }

	// 生存していない場合は弾生成
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	tkl::Vector3 nearPos;
	for (auto it = list->begin(); it != list->end(); ++it) {
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);
		tkl::Vector3 pos = unit->GetUnitPosition();
		float dist = tkl::Vector3::Distance(pos, mMesh->GetPosition());
		if (dist <= CREATE_DISTANCE) { nearPos = pos; break; }
	}
	if (tkl::Vector3::Magnitude(nearPos) == 0) { return; }

	// 弾関連処理
	mBullet = ObjectManager::GetInstance()->Create<Bullet>(mParam);
	std::shared_ptr<Bullet> bullet = mBullet.lock();
	bullet->SetLauncherPos(mMesh->GetPosition());
	bullet->SetTargetPos(nearPos);
	bullet->Initialize();
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：なし
// 戻り値：なし
// 詳　細：防衛ユニットクラスの描画処理
//****************************************************************************
void DefenseUnit::Draw()
{
	mMesh->Draw(mParam->GetCamera());
}