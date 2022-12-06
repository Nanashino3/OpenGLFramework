#ifndef _ADVANCEUNITMANAGER_H_
#define _ADVANCEUNITMANAGER_H_

#include "ObjectPool.h"
#include "AdvanceUnit.h"
class AdvanceUnitManager
{
public:
	static AdvanceUnitManager* GetInstance();
	static void DestroyInstance();

	void CreateUnit(int mapSize, int mapRow, int mapColumn, std::vector<tkl::CELL>& route, float moveSpeed = 10.0f);
	void Update(float deltaTime, std::shared_ptr<tkl::Camera>& camera, std::vector<tkl::CELL>& newRoute);

private:
	AdvanceUnitManager();
	~AdvanceUnitManager();

private:
	static AdvanceUnitManager* sMyInstance;
	std::list<std::shared_ptr<AdvanceUnit>> mList;
};

#endif