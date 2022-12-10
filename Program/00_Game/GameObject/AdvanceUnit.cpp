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

void AdvanceUnit::Update(std::shared_ptr<GameParameter> param)
{
	SetNewRoute(param->GetRoute());
	Move(param);
	Draw(param);
}

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

void AdvanceUnit::Draw(std::shared_ptr<GameParameter> param)
{
	mMesh->Draw(param->GetCamera());
}

// 最新ルート設定
void AdvanceUnit::SetNewRoute(std::vector<tkl::CELL>& newRoute)
{
	int prevSize = mRoute.size();
	int currentSize = newRoute.size();

	mRoute = newRoute;
	mRouteCount = mRouteCount + abs(prevSize - currentSize);
}

tkl::Vector3 AdvanceUnit::GetUnitPosition() const
{
	return mMesh->GetPosition();
}