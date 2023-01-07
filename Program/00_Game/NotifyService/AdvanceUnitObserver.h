//****************************************************************************
// ファイル名：AdvanceUnitObserver(進軍ユニットオブザーバー)
// 作　成　日：2022/12/11
#ifndef _ADVANCEUNITOBSERVER_H_
#define _ADVANCEUNITOBSERVER_H_

#include "Observer.h"

class AdvanceUnitObserver : public Observer
{
public:
	AdvanceUnitObserver();
	virtual ~AdvanceUnitObserver();

	virtual void FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param);
};

#endif