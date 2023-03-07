//****************************************************************************
// ファイル名：Notifier(通知者クラス)
// 作　成　日：2022/12/11
#include "Notifier.h"

#include "Observer.h"
#include "../../02_Library/Utility.h"

Notifier* Notifier::sMyInstance = nullptr;
Notifier::Notifier()
{}

Notifier::~Notifier()
{}

Notifier* Notifier::GetInstance()
{
	if(!sMyInstance){ sMyInstance = new Notifier; }
	return sMyInstance;
}

void Notifier::DestroyInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// 関数名：FieldStateChange
// 概　要：フィールド状態変化
// 引　数：arg1 フィールドの行
//       ：arg2 フィールドの列
//       ：arg3 ゲームパラメータ
// 戻り値：なし
// 詳　細：フィールドの状態が変化したことを通知する
//****************************************************************************
void Notifier::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	for(int i = 0; i < mObservers.size(); ++i){
		mObservers[i]->FieldStateChange(row, column, param);
	}
}

//****************************************************************************
// 関数名：DefeatAdvanceUnit
// 概　要：進軍ユニット撃破通知
// 引　数：arg1 ゲームパラメータ
//       ：arg2 撃破時の位置
// 戻り値：なし
// 詳　細：進軍ユニットを撃破したことを通知する
//****************************************************************************
void Notifier::DefeatAdvanceUnit(std::shared_ptr<GameParameter> param, const tkl::Vector3& position)
{
	for(int i = 0; i < mObservers.size(); ++i){
		mObservers[i]->DefeatAdvanceUnit(param, position);
	}
}