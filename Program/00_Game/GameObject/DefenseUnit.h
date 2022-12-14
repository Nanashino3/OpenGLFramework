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
public:
	DefenseUnit(std::shared_ptr<GameParameter> param);
	virtual ~DefenseUnit();

	virtual void Update(std::shared_ptr<GameParameter>& param) final;
	virtual void Draw(std::shared_ptr<GameParameter>& param) final;
private:
	std::shared_ptr<tkl::Mesh> mMesh;
	std::weak_ptr<Bullet> mBullet;
};

#endif