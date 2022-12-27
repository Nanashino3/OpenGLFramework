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
namespace tkl{
//class Mesh;
class Model;
class Sound;
}

class DefenseUnit : public GameObject
{
public:
	DefenseUnit(std::shared_ptr<Parameter> param);
	virtual ~DefenseUnit();

	virtual void Initialize() final;
	virtual void Update() final;
	virtual void Draw() final;
private:
	float mElapsed;
	std::shared_ptr<GameParameter> mParam;
	std::weak_ptr<Bullet> mBullet;

	//std::shared_ptr<tkl::Mesh> mMesh;
	std::shared_ptr<tkl::Model> mModel;
	std::shared_ptr<tkl::Sound> mSound;
};

#endif