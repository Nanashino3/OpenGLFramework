//****************************************************************************
// ファイル名：DefenseUnitObserver(防衛ユニットオブザーバー)
// 作　成　日：2022/12/11
#include "DefenseUnitObserver.h"

#include "../GameObject/DefenseUnit.h"
#include "../GameObject/ObjectManager.h"
#include "../GameObject/GameParameter.h"

static constexpr int CONSUME_COST = 75;

DefenseUnitObserver::DefenseUnitObserver()
{}

DefenseUnitObserver::~DefenseUnitObserver()
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
void DefenseUnitObserver::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	std::vector<std::vector<tkl::CELL>> fields = param->GetFields();

	// 防衛ユニット生成
	if((fields[row][column].status == tkl::STATUS::OBSTACLE) &&
	   (param->GetTotalCost() >= CONSUME_COST)) {
		fields[row][column].status = tkl::STATUS::UNIT;
		std::shared_ptr<DefenseUnit> newObject = ObjectManager::GetInstance()->Create<DefenseUnit>(param);
		newObject->Initialize();
	}else{
		fields[row][column].status = tkl::STATUS::EDITABLE;
	}
	param->SetFields(fields);
}