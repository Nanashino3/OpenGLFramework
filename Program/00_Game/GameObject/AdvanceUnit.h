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
	AdvanceUnit(int mapSize, int mapDiv, std::vector<tkl::CELL>& route);
	~AdvanceUnit();

	void Move(float deltaTime);
	void Draw(std::shared_ptr<tkl::Camera>& camera);

private:
	std::shared_ptr<tkl::Mesh> mMesh;

	int mMapSize;
	int mRouteCount;
	float mFirstPosX, mFirstPosZ;
	std::vector<tkl::CELL> mRoute;
};

#endif