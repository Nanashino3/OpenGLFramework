#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <memory>
class GameParameter;
class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}

	virtual void FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param) {}
};

#endif