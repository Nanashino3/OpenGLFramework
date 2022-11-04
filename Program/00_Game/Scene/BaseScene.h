#ifndef _BASESCENE_H_
#define _BASESCENE_H_

#include <memory>
class BaseScene
{
public:
	BaseScene(){}
	virtual ~BaseScene(){}

	virtual std::shared_ptr<BaseScene> Update() = 0;
};

#endif