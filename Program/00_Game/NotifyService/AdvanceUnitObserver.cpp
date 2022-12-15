//****************************************************************************
// ファイル名：AdvanceUnitObserver(進軍ユニットオブザーバー)
// 作　成　日：2022/12/11
#include "AdvanceUnitObserver.h"

#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/ObjectManager.h"
#include "../GameObject/GameParameter.h"

AdvanceUnitObserver::AdvanceUnitObserver()
{}

AdvanceUnitObserver::~AdvanceUnitObserver()
{}

//****************************************************************************
// 関数名：FieldStateChange
// 概　要：フィールド状態変化
// 引　数：arg1 フィールドの行
//       ：arg2 フィールドの列
//       ：arg3 ゲームパラメータ
// 戻り値：なし
// 詳　細：フィールドの状態が変化したことを通知する
//****************************************************************************
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
		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		for(auto it = list->begin(); it != list->end(); ++it){
			std::shared_ptr<AdvanceUnit> unit = std::dynamic_pointer_cast<AdvanceUnit>(*it);
			unit->SetNewRoute(newRoute);
		}
	}else{
		fields[row][column].status = tkl::STATUS::EDITABLE;
	}
	param->SetFields(fields);
}