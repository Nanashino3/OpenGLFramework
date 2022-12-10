#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <memory>
class GameParameter;
class GameObject
{
public:
	GameObject() : mIsAlive(true){}
	virtual ~GameObject(){}

	virtual void Update(std::shared_ptr<GameParameter> param) = 0;
	virtual bool IsAlive(){ return mIsAlive; }

protected:
	bool mIsAlive;
};

#endif