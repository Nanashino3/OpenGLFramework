//****************************************************************************
// ファイル名：GameScene(ゲーム画面クラス)
// 作　成　日：2022/12/15
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

class Field;
class GameParameter;
namespace tkl
{
class Camera;
class Mesh;
class Sound;
}

class GameScene : public SceneBase
{
public:
	GameScene(std::shared_ptr<SceneManager> manager);
	virtual ~GameScene();

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	int mDurability;
	float mElapsedTime;

	std::shared_ptr<Field> mField;
	std::shared_ptr<GameParameter> mParam;
	std::shared_ptr<tkl::Camera> m3DCam;
	std::shared_ptr<tkl::Camera> m2DCam;
	std::shared_ptr<tkl::Mesh> mbgTex;
	std::shared_ptr<tkl::Sound> mSndBgm;
	std::shared_ptr<tkl::Sound> mSndPause;
};

#endif