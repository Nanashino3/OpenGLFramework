//****************************************************************************
// ファイル名：GameScene(ゲーム画面クラス)
// 作　成　日：2022/12/15
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"
#include <list>

class Field;
class UiBase;
class UiDurability;
class UiCollect;
class EffectBase;
class GameParameter;
namespace tkl
{
class Camera;
class Mesh;
class Sound;
}

class GameScene : public SceneBase, public std::enable_shared_from_this<GameScene>
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void AddEffect(std::shared_ptr<EffectBase> effect){ mEffectList.emplace_back(effect); }

private:
	int mDurability;
	float mElapsedTime;

	std::shared_ptr<Field> mField;
	std::shared_ptr<UiDurability> mUiDurability;
	std::shared_ptr<UiCollect> mUiCollect;
	std::shared_ptr<GameParameter> mParam;

	std::shared_ptr<tkl::Camera> m3DCam;
	std::shared_ptr<tkl::Camera> m2DCam;
	std::shared_ptr<tkl::Mesh> mbgTex;
	std::shared_ptr<tkl::Sound> mSndBgm;
	std::shared_ptr<tkl::Sound> mSndPause;

	std::list<std::shared_ptr<UiBase>> mUiList;
	std::list<std::shared_ptr<EffectBase>> mEffectList;
};

#endif