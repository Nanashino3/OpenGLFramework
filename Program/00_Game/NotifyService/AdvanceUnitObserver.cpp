#include "AdvanceUnitObserver.h"

#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/ObjectManager.h"
#include "../GameObject/GameParameter.h"

AdvanceUnitObserver::AdvanceUnitObserver()
{}

AdvanceUnitObserver::~AdvanceUnitObserver()
{}

void AdvanceUnitObserver::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	int mapRow = param->GetMapRow();
	int mapColumn = param->GetMapColumn();
	auto fields = param->GetFields();

	// 編集不可状態にしておく
	fields[row][column].status = tkl::STATUS::UNEDITABLE;

	// 経路再探索
	std::vector<tkl::CELL> newRoute;
	if(tkl::Algorithm::RouteSearch(mapRow, mapColumn, fields, newRoute)) {
		param->SetRoute(newRoute);
	}else{
		fields[row][column].status = tkl::STATUS::EDITABLE;
	}
	param->SetFields(fields);
}