#include "DefenseUnitManager.h"

DefenseUnitManager* DefenseUnitManager::sMyInstance = nullptr;
DefenseUnitManager::DefenseUnitManager()
{}

DefenseUnitManager::~DefenseUnitManager()
{}

DefenseUnitManager* DefenseUnitManager::GetInstance()
{
	if(!sMyInstance) sMyInstance = new DefenseUnitManager;
	return sMyInstance;
}

void DefenseUnitManager::DestroyInstance()
{
	delete sMyInstance;
}

// ���j�b�g����
void DefenseUnitManager::CreateUnit(const tkl::Vector3& pos)
{
	std::shared_ptr<DefenseUnit> unit = std::make_shared<DefenseUnit>(pos);
	mList.emplace_back(unit);
}

// ���j�b�g�X�V
void DefenseUnitManager::Update(float deltaTime, std::shared_ptr<tkl::Camera>& camera)
{
	for (auto unit : mList) {
		unit->Update(deltaTime, camera);
	}
}