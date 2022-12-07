// –h‰qƒ†ƒjƒbƒg
#ifndef _DEFENSEUNIT_H_
#define _DEFENSEUNIT_H_

#include <list>
#include <memory>
#include "GameObject.h"

class Bullet;
class GameParameter;
namespace tkl{ class Mesh; }

class DefenseUnit : public GameObject
{
public:
	DefenseUnit(std::shared_ptr<GameParameter> param);
	virtual ~DefenseUnit();

	virtual void Update(std::shared_ptr<GameParameter> param) final;

private:


private:
	std::shared_ptr<tkl::Mesh> mMesh;
	std::weak_ptr<Bullet> mBullet;
};

#endif