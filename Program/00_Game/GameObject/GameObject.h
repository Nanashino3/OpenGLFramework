//****************************************************************************
// ファイル名：GameObject(ゲームオブジェクトクラス)
// 作　成　日：2022/12/8
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <memory>

class Parameter;
class GameObject
{
public:
	GameObject() : mIsAlive(true){}
	virtual ~GameObject(){}

#if 1
	virtual void Initialize(){}
	virtual void Collision(){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
#else
	virtual void Collision() {}
	virtual void Update(std::shared_ptr<GameParameter>& param) = 0;
	virtual void Draw(std::shared_ptr<GameParameter>& param) = 0;
#endif

	virtual bool IsAlive(){ return mIsAlive; }

protected:
	bool mIsAlive;
	std::shared_ptr<Parameter> mParam;
};

#endif