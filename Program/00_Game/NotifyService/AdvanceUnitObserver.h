// 進軍ユニットオブザーバー
#ifndef _ADVANCEUNITOBSERVER_H_
#define _ADVANCEUNITOBSERVER_H_

#include "Observer.h"

class AdvanceUnitObserver : public Observer
{
public:
	AdvanceUnitObserver();
	virtual ~AdvanceUnitObserver();

	virtual void FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param) final;
};

#endif