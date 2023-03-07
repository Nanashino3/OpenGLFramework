//****************************************************************************
// ファイル名：Observer(基底オブザーバークラス)
// 作　成　日：2022/12/11
#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <memory>

namespace tkl
{
class Vector3;
}
class GameParameter;

class Observer
{
public:
	Observer(){}
	virtual ~Observer(){}

	virtual void FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param){}
	virtual void DefeatAdvanceUnit(std::shared_ptr<GameParameter> param, const tkl::Vector3& position){}
};

#endif