//****************************************************************************
// ファイル名：Notifier(通知者クラス)
// 作　成　日：2022/12/11
#include "Notifier.h"

#include "Observer.h"

Notifier* Notifier::sMyInstance = nullptr;
Notifier::Notifier()
{}

Notifier::~Notifier()
{}

Notifier* Notifier::GetInstance()
{
	if(!sMyInstance) sMyInstance = new Notifier;
	return sMyInstance;
}

void Notifier::DestroyInstance()
{
	delete sMyInstance;
}

//****************************************************************************
// 関数名：FieldStateChange
// 概　要：フィールド状態変化
// 引　数：arg1 行
//       ：arg2 列
//       ：arg3 ゲームパラメータ
// 戻り値：なし
// 詳　細：フィールドの状態に変化があったことを通知する
//****************************************************************************
void Notifier::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	for(int i = 0; i < mObservers.size(); ++i){
		mObservers[i]->FieldStateChange(row, column, param);
	}
}