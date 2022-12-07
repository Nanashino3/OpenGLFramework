#include "AdvanceUnit.h"

#include "GameParameter.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

AdvanceUnit::AdvanceUnit(std::shared_ptr<GameParameter> param)
: mMapSize(param->GetMapSize())
, mRouteCount(0)
, mFirstPosX(0), mFirstPosZ(0)
, mMoveSpeed(10.0f)
, mMesh(nullptr)
, mRoute(param->GetRoute())
{
	int mapSize = param->GetMapSize();
	int mapRow = param->GetMapRow();
	int mapColumn = param->GetMapColumn();

	mRouteCount = param->GetRoute().size() - 1;
	mMesh = tkl::Mesh::CreateBox(25);

	// 初期座標計算
	mFirstPosX = -mMapSize * mapRow * 0.5f + (mMapSize >> 1);
	mFirstPosZ = -mMapSize * mapColumn * 0.5f + (mMapSize >> 1);

	mMesh->SetPosition(tkl::Vector3(mFirstPosX, (mMapSize >> 1), mFirstPosZ));
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
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
	tkl::Vector3 pos = mMesh->GetPosition();

	float targetPosX = mFirstPosX + mMapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mMapSize * mRoute[mRouteCount - 1].row;

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
			if (mRouteCount > 1) mRouteCount--;
		}
	} else if (dx < 0 || dz < 0) {
		if (pos.mX < targetPosX || pos.mZ < targetPosZ) {
			pos.mX = targetPosX; pos.mZ = targetPosZ;
			if (mRouteCount > 1) mRouteCount--;
		}
	}
	//******************************************************************
	
	mMesh->SetPosition(pos);
}

void AdvanceUnit::Draw(std::shared_ptr<GameParameter> param)
{
	mMesh->Draw(param->GetCamera());
}

// 生存しているか
bool AdvanceUnit::IsAlive()
{
	if(mRoute[mRouteCount - 1].status != tkl::STATUS::GOAL) return true;

	tkl::Vector3 pos = mMesh->GetPosition();
	float targetPosX = mFirstPosX + mMapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mMapSize * mRoute[mRouteCount - 1].row;

	return !(pos.mX == targetPosX && pos.mZ == targetPosZ);
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