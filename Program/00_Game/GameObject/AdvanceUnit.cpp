//****************************************************************************
// ファイル名：AdvanceUnit(進軍ユニットクラス)
// 作　成　日：2022/12/4
#include "AdvanceUnit.h"

#include "GameParameter.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

AdvanceUnit::AdvanceUnit(std::shared_ptr<GameParameter> param)
: mRouteCount(0)
, mFirstPosX(0), mFirstPosZ(0)
, mMoveSpeed(15.0f)
, mMesh(nullptr)
{
	int mapSize = param->GetMapSize();
	int mapRow = param->GetMapRow();
	int mapColumn = param->GetMapColumn();
	auto field = param->GetFields();

	// 経路検索(初期)
	tkl::Algorithm::RouteSearch(mapRow, mapColumn, field, mRoute);

	mRouteCount = mRoute.size() - 1;
	mMesh = tkl::Mesh::CreateBox(25);

	// 初期座標計算
	mFirstPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	mFirstPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	mMesh->SetPosition(tkl::Vector3(mFirstPosX, (mapSize >> 1), mFirstPosZ));
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));

	// パラメータ設定
	param->SetRoute(mRoute);
}

AdvanceUnit::~AdvanceUnit()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：進軍ユニットクラスの更新処理
//****************************************************************************
void AdvanceUnit::Update(std::shared_ptr<GameParameter>& param)
{
	SetNewRoute(param->GetRoute());
	Move(param);
	Draw(param);
}

//****************************************************************************
// 関数名：Move(private)
// 概　要：移動
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：進軍ユニットクラスの移動処理
//****************************************************************************
void AdvanceUnit::Move(std::shared_ptr<GameParameter> param)
{
	if(mRouteCount == 0 && mRoute[mRouteCount].status == tkl::STATUS::GOAL){ mIsAlive = false; return; }

	tkl::Vector3 pos = mMesh->GetPosition();
	int mapSize = param->GetMapSize();

	float targetPosX = mFirstPosX + mapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mapSize * mRoute[mRouteCount - 1].row;

	// 移動量計算
	int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	//******************************************************************
	// 探索した経路を進む処理
	pos.mX += mMoveSpeed * dx * param->GetDeltaTime();
	pos.mZ += mMoveSpeed * dz * param->GetDeltaTime();

	if (dx > 0 || dz > 0) {
		if (pos.mX > targetPosX || pos.mZ > targetPosZ) {
			pos.mX = targetPosX; pos.mZ = targetPosZ;
			if (mRouteCount > 0) mRouteCount--;
		}
	} else if (dx < 0 || dz < 0) {
		if (pos.mX < targetPosX || pos.mZ < targetPosZ) {
			pos.mX = targetPosX; pos.mZ = targetPosZ;
			if (mRouteCount > 0) mRouteCount--;
		}
	}
	//******************************************************************
	
	mMesh->SetPosition(pos);
}

//****************************************************************************
// 関数名：Draw(private)
// 概　要：描画
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：進軍ユニットクラスの描画処理
//****************************************************************************
void AdvanceUnit::Draw(std::shared_ptr<GameParameter> param)
{
	mMesh->Draw(param->GetCamera());
}

//****************************************************************************
// 関数名：SetNewRoute(private)
// 概　要：最新ルート設定
// 引　数：arg1 最新ルート
// 戻り値：なし
// 詳　細：最新のルートを設定する
//****************************************************************************
void AdvanceUnit::SetNewRoute(std::vector<tkl::CELL>& newRoute)
{
	int prevSize = mRoute.size();
	int currentSize = newRoute.size();

	mRoute = newRoute;
	mRouteCount = mRouteCount + abs(prevSize - currentSize);
}

//****************************************************************************
// 関数名：GetUnitPosition
// 概　要：ユニット位置を取得
// 引　数：なし
// 戻り値：ユニットの位置
// 詳　細：進軍ユニット自身の位置を返す
//****************************************************************************
tkl::Vector3 AdvanceUnit::GetUnitPosition() const
{
	return mMesh->GetPosition();
}