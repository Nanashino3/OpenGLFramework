//****************************************************************************
// �t�@�C�����FGameScene(�Q�[����ʃN���X)
// ��@���@���F2022/12/15
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

class Field;
class GameParameter;
namespace tkl{
class Camera;
class Mesh;
class Sound;
}
class GameScene : public SceneBase
{
public:
	GameScene(std::shared_ptr<SceneManager> manager);
	virtual ~GameScene();

	virtual void Initialize() final;
	virtual void Update(float deltaTime) final;
	virtual void Draw() final;

private:
	float mElapsed;
	int mDurability;
	std::shared_ptr<GameParameter> mParam;
	std::shared_ptr<tkl::Camera> m3DCam;
	std::shared_ptr<tkl::Camera> m2DCam;

	std::shared_ptr<tkl::Mesh> mbgTex;
	std::shared_ptr<Field> mField;
	std::shared_ptr<tkl::Sound> mSndBgm;
	std::shared_ptr<tkl::Sound> mSndPause;
};

#endif