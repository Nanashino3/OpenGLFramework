//****************************************************************************
// ファイル名：GameObject(ゲームオブジェクトクラス)
// 作　成　日：2022/12/8
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <memory>
#include "../../02_Library/Vector.h"

class GameParameter;
class GameObject
{
public:
	GameObject() : mIsAlive(true){}
	virtual ~GameObject(){}

	virtual void Collision() {}
	virtual void Update(std::shared_ptr<GameParameter>& param) = 0;
	virtual void Draw(std::shared_ptr<GameParameter>& param) = 0;
	virtual bool IsAlive(){ return mIsAlive; }

protected:
	bool mIsAlive;
};

#endif