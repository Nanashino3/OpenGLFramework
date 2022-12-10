#include "DefenseUnitObserver.h"

#include "../GameObject/DefenseUnit.h"
#include "../GameObject/ObjectManager.h"
#include "../GameObject/GameParameter.h"

DefenseUnitObserver::DefenseUnitObserver()
{}

DefenseUnitObserver::~DefenseUnitObserver()
{}

void DefenseUnitObserver::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	auto fields = param->GetFields();

	// –h‰qƒ†ƒjƒbƒg¶¬
	if(fields[row][column].status == tkl::STATUS::UNEDITABLE){
		fields[row][column].status = tkl::STATUS::UNIT;
		ObjectManager::GetInstance()->Create<DefenseUnit>(param);
	}
	param->SetFields(fields);
}