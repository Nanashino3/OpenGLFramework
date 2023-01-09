//****************************************************************************
// �t�@�C�����FObserver(���I�u�U�[�o�[�N���X)
// ��@���@���F2022/12/11
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