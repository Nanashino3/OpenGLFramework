//****************************************************************************
// ファイル名：AdvanceUnit(進軍ユニットクラス)
// 作　成　日：2022/12/4
#include "AdvanceUnit.h"

#include "GameParameter.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../02_Library/Utility.h"

AdvanceUnit::AdvanceUnit(std::shared_ptr<Parameter> param)
: mRouteCount(0)
, mFirstPosX(0), mFirstPosZ(0)
, mMoveSpeed(0)
, mHitPoint(0)
, mAddCoin(0)
, mMesh(nullptr)
{
	mUnitInfo = tkl::LoadCsv(CSV_PATH);
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
}

AdvanceUnit::~AdvanceUnit()
{}

void AdvanceUnit::Initialize()
{
	int mapSize = mParam->GetMapSize();
	int mapRow = mParam->GetMapRow();
	int mapColumn = mParam->GetMapColumn();
	auto field = mParam->GetFields();

	// 経路検索(初期)
	tkl::Algorithm::RouteSearch(mapRow, mapColumn, field, mRoute);

	mRouteCount = mRoute.size() - 1;
	mMesh = tkl::Mesh::CreateBox(25);

	// 初期座標計算
	mFirstPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	mFirstPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	mMesh->SetPosition(tkl::Vector3(mFirstPosX, (mapSize >> 1), mFirstPosZ));
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));

	int level = mParam->GetAdvenceLevel();
	if(stoi(mUnitInfo[level][0]) <= mParam->GetTotalDefeat() && (level + 1) < mUnitInfo.size()){
		mParam->SetAdvanceLevel(level + 1);
		mParam->SetTotalDefeat(0);
	}
	mHitPoint = stoi(mUnitInfo[level][1]);
	mMoveSpeed = stoi(mUnitInfo[level][2]);
	mAddCoin = stoi(mUnitInfo[level][3]);
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：進軍ユニットクラスの更新処理
//****************************************************************************
void AdvanceUnit::Update()
{
	if (mRouteCount == 0 && mRoute[mRouteCount].status == tkl::STATUS::GOAL) {
		mIsAlive = false;
		mParam->SetIsArrival(true);
		return;
	}

	tkl::Vector3 pos = mMesh->GetPosition();
	int mapSize = mParam->GetMapSize();

	float targetPosX = mFirstPosX + mapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mapSize * mRoute[mRouteCount - 1].row;

	// 移動量計算
	int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	//******************************************************************
	// 探索した経路を進む処理
	pos.mX += mMoveSpeed * dx * mParam->GetDeltaTime();
	pos.mZ += mMoveSpeed * dz * mParam->GetDeltaTime();

	if(dx > 0 || dz > 0){
		if(pos.mX > targetPosX || pos.mZ > targetPosZ){
			pos.mX = targetPosX; pos.mZ = targetPosZ;
			if(mRouteCount > 0) mRouteCount--;
		}
	}else if(dx < 0 || dz < 0){
		if(pos.mX < targetPosX || pos.mZ < targetPosZ){
			pos.mX = targetPosX; pos.mZ = targetPosZ;
			if(mRouteCount > 0) mRouteCount--;
		}
	}
	//******************************************************************

	mMesh->SetPosition(pos);
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：進軍ユニットクラスの描画処理
//****************************************************************************
void AdvanceUnit::Draw()
{
	mMesh->Draw(mParam->GetCamera());
}

//****************************************************************************
// 関数名：IsAlive
// 概　要：生存しているか
// 引　数：なし
// 戻り値：なし
// 詳　細：生存しているかの確認
//****************************************************************************
bool AdvanceUnit::IsAlive()
{
	if(!mIsAlive && mHitPoint <= 0){
		mParam->SetTotalCost(mParam->GetTotalCost() + mAddCoin);
		mParam->SetTotalDefeat(mParam->GetTotalDefeat() + 1);
	}
	return mIsAlive;
}

//****************************************************************************
// 関数名：ReceiveDamage
// 概　要：ダメージを受ける
// 引　数：arg1 受けるダメージ数
// 戻り値：なし
// 詳　細：ダメージの処理をする(TODO：もっといい方法があれば作り変える)
//****************************************************************************
void AdvanceUnit::ReceiveDamage(int damage)
{
	mHitPoint -= damage;
	if(mHitPoint <= 0){ mIsAlive = false; }
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

//****************************************************************************
// 関数名：SetNewRoute(private)
// 概　要：最新ルート設定
// 引　数：arg1 最新ルート
// 戻り値：なし
// 詳　細：最新のルートを設定する
//****************************************************************************
void AdvanceUnit::SetNewRoute(const std::vector<tkl::CELL>& newRoute)
{
	int prevSize = mRoute.size();
	int currentSize = newRoute.size();

	mRoute = newRoute;
	mRouteCount = mRouteCount + abs(prevSize - currentSize);
}