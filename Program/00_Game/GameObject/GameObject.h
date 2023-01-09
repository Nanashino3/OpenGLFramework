//****************************************************************************
// �t�@�C�����FGameObject(�Q�[���I�u�W�F�N�g�N���X)
// ��@���@���F2022/12/8
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <memory>

class Parameter;

class GameObject
{
public:
	GameObject()
	: mIsAlive(true), mParam(nullptr)
	{}
	virtual ~GameObject(){}

	virtual void Collision(){}
	virtual void Update(){}
	virtual void Draw() = 0;

	virtual bool IsAlive(){ return mIsAlive; }

protected:
	bool mIsAlive;
	std::shared_ptr<Parameter> mParam;
};

#endif