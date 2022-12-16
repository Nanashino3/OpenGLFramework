//****************************************************************************
// ファイル名：DefenseUnit(防衛ユニットクラス)
// 作　成　日：2022/12/5
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
	const float CREATE_DISTANCE = 55.0f;
	const int CONSUME_COST = 25;
public:
	DefenseUnit(std::shared_ptr<Parameter> param);
	virtual ~DefenseUnit();

	virtual void Initialize() final;
	virtual void Update() final;
	virtual void Draw() final;
private:
	std::shared_ptr<tkl::Mesh> mMesh;
	std::shared_ptr<GameParameter> mParam;
	std::weak_ptr<Bullet> mBullet;
};

#endif