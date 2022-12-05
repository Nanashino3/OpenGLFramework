// 進軍ユニット
#include "AdvanceUnit.h"

#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

AdvanceUnit::AdvanceUnit(int mapSize, int mapRow, int mapColumn, std::vector<tkl::CELL>& route, float moveSpeed)
: mMesh(nullptr)
, mMapSize(mapSize)
, mRouteCount(0)
, mFirstPosX(0), mFirstPosZ(0)
, mRoute(route)
, mMoveSpeed(moveSpeed)
{
	mRouteCount = route.size() - 1;	// 0オリジン
	mMesh = tkl::Mesh::CreateBox(25);

	// 初期座標計算
	mFirstPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	mFirstPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);
	mMesh->SetPosition(tkl::Vector3(mFirstPosX, (mapSize >> 1), mFirstPosZ));
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
}

AdvanceUnit::~AdvanceUnit()
{}

void AdvanceUnit::Move(float deltaTime)
{
	tkl::Vector3 pos = mMesh->GetPosition();
	float targetPosX = mFirstPosX + mMapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mMapSize * mRoute[mRouteCount - 1].row;

	// 移動量計算
	int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	//******************************************************************
	// 探索した経路を進む処理
	pos.mX += mMoveSpeed * dx * deltaTime;
	pos.mZ += mMoveSpeed * dz * deltaTime;

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

void AdvanceUnit::Draw(std::shared_ptr<tkl::Camera>& camera)
{
	mMesh->Draw(camera);
}

// 目標地点か
bool AdvanceUnit::IsTargetPoint()
{
	if(mRoute[mRouteCount - 1].status != tkl::STATUS::GOAL) return false;

	tkl::Vector3 pos = mMesh->GetPosition();
	float targetPosX = mFirstPosX + mMapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mMapSize * mRoute[mRouteCount - 1].row;

	return pos.mX == targetPosX && pos.mZ == targetPosZ;
}

// 最新ルート設定
void AdvanceUnit::SetNewRoute(std::vector<tkl::CELL>& newRoute)
{
	int prevSize = mRoute.size();
	int currentSize = newRoute.size();

	mRoute = newRoute;
	mRouteCount = mRouteCount + abs(prevSize - currentSize);
}