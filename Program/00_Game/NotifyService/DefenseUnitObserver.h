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