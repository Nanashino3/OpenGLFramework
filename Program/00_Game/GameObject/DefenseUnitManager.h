#ifndef _DEFENSEUNIITMANAGER_H_
#define _DEFENSEUNIITMANAGER_H_

#include <list>
#include "DefenseUnit.h"

namespace tkl{
class Vector3;
}

class DefenseUnitManager
{
public:
	static DefenseUnitManager* GetInstance();
	static void DestroyInstance();

	void CreateUnit(const tkl::Vector3& pos);
	void Update(float deltaTime, std::shared_ptr<tkl::Camera>& camera);

private:
	DefenseUnitManager();
	~DefenseUnitManager();

private:
	static DefenseUnitManager* sMyInstance;
	std::list<std::shared_ptr<DefenseUnit>> mList;
};

#endif