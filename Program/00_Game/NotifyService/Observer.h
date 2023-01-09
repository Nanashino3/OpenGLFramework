//****************************************************************************
// ファイル名：Observer(基底オブザーバークラス)
// 作　成　日：2022/12/11
#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <memory>

class GameParameter;

class Observer
{
public:
	Observer(){}
	virtual ~Observer(){}

	virtual void FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param){}
};

#endif