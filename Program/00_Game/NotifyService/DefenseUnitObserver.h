//****************************************************************************
// ファイル名：DefenseUnitObserver(防衛ユニットオブザーバー)
// 作　成　日：2022/12/11
#ifndef _DEFENSEUNITOBSERVER_H_
#define _DEFENSEUNITOBSERVER_H_

#include "Observer.h"

class DefenseUnitObserver : public Observer
{
public:
	DefenseUnitObserver();
	virtual ~DefenseUnitObserver();

	virtual void FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param) final;
};

#endif