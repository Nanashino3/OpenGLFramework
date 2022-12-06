#include "AdvanceUnitManager.h"

AdvanceUnitManager* AdvanceUnitManager::sMyInstance = nullptr;
AdvanceUnitManager::AdvanceUnitManager()
{}

AdvanceUnitManager::~AdvanceUnitManager()
{}

AdvanceUnitManager* AdvanceUnitManager::GetInstance()
{
	if(!sMyInstance){ sMyInstance = new AdvanceUnitManager(); }
	return sMyInstance;
}

void AdvanceUnitManager::DestroyInstance()
{
	delete sMyInstance;
}

// ユニット生成
void AdvanceUnitManager::CreateUnit(int mapSize, int mapRow, int mapColumn, std::vector<tkl::CELL>& route, float moveSpeed)
{
	std::shared_ptr<AdvanceUnit> unit = std::make_shared<AdvanceUnit>(mapSize, mapRow, mapColumn, route, moveSpeed);
	mList.emplace_back(unit);
}

// ユニット更新
void AdvanceUnitManager::Update(float deltaTime, std::shared_ptr<tkl::Camera>& camera, std::vector<tkl::CELL>& newRoute)
{
	for (auto iter = mList.begin(); iter != mList.end();) {
		(*iter)->SetNewRoute(newRoute);
		(*iter)->Update(deltaTime, camera);
		if ((*iter)->IsAlive()) { iter = mList.erase(iter); continue; }
		++iter;
	}
}