#include "AdvanceUnit.h"

#include "../../01_Engine/Mesh.h"

AdvanceUnit::AdvanceUnit(int mapSize, int mapDiv, std::vector<tkl::CELL>& route)
: mMesh(nullptr)
, mMapSize(mapSize)
, mRouteCount(0)
, mFirstPosX(0), mFirstPosZ(0)
, mRoute(route)
{
	mRouteCount = route.size() - 1;	// 0ƒIƒŠƒWƒ“
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);

	// ‰ŠúÀ•WŒvŽZ
	mFirstPosX = -mapSize * mapDiv * 0.5f + (mapSize >> 1);
	mFirstPosZ = mFirstPosX;
	mMesh->SetPosition(tkl::Vector3(mFirstPosX, (mapSize >> 1), mFirstPosZ));
}

AdvanceUnit::~AdvanceUnit()
{}

void AdvanceUnit::Move(float deltaTime)
{
	tkl::Vector3 pos = mMesh->GetPosition();
	float targetPosX = mFirstPosX + mMapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mMapSize * mRoute[mRouteCount - 1].row;

	// ˆÚ“®—ÊŒvŽZ
	int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	//******************************************************************
	// ’Tõ‚µ‚½Œo˜H‚ði‚Þˆ—
	pos.mX += 3.0f * dx * deltaTime;
	pos.mZ += 3.0f * dz * deltaTime;

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