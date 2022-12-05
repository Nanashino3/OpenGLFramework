#ifndef _ADVANCEUNIT_H_
#define _ADVANCEUNIT_H_

#include <memory>
#include <vector>
#include "../../01_Engine/Algorithm.h"

namespace tkl{
class Mesh;
class Camera;
}

class AdvanceUnit
{
public:
	AdvanceUnit(int mapSize, int mapRow, int mapColumn, std::vector<tkl::CELL>& route, float moveSpeed = 10.0f);
	~AdvanceUnit();

	void Move(float deltaTime);
	void Draw(std::shared_ptr<tkl::Camera>& camera);

	bool IsTargetPoint();

	void SetNewRoute(std::vector<tkl::CELL>& newRoute);

private:
	std::shared_ptr<tkl::Mesh> mMesh;

	int mMapSize;
	int mRouteCount;
	float mFirstPosX, mFirstPosZ;
	std::vector<tkl::CELL> mRoute;
	float mMoveSpeed;
};

#endif