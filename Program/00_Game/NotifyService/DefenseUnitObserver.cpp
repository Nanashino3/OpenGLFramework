//****************************************************************************
// ファイル名：DefenseUnitObserver(防衛ユニットオブザーバー)
// 作　成　日：2022/12/11
#include "DefenseUnitObserver.h"

#include "../GameObject/DefenseUnit.h"
#include "../GameObject/ObjectManager.h"
#include "../GameObject/GameParameter.h"

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
	auto fields = param->GetFields();

	// 防衛ユニット生成
	if((fields[row][column].status == tkl::STATUS::UNEDITABLE) && 
	   (param->GetTotalCost() >= 25)) {
		fields[row][column].status = tkl::STATUS::UNIT;
		ObjectManager::GetInstance()->Create<DefenseUnit>(param);
	}
	param->SetFields(fields);
}