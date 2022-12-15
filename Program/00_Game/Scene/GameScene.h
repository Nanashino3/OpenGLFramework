//****************************************************************************
// ファイル名：GameScene(ゲーム画面クラス)
// 作　成　日：2022/12/15
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

class Field;
class GameParameter;
namespace tkl {
class Camera;
}
class GameScene : public SceneBase
{
	const int CREATE_MAX = 5;
public:
	GameScene(std::shared_ptr<SceneManager> manager);
	virtual ~GameScene();

	virtual void Initialize() final;
	virtual void Update(float deltaTime) final;
	virtual void Draw() final;

private:
	float mElapsed;
	int mEndurance;
	std::shared_ptr<GameParameter> mParam;
	std::shared_ptr<tkl::Camera> mCamera;

	std::shared_ptr<Field> mField;
};

#endif