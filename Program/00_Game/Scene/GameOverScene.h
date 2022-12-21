//****************************************************************************
// �t�@�C�����FGameScene(�Q�[����ʃN���X)
// ��@���@���F2022/12/15
#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_

#include "SceneBase.h"
namespace tkl{ class Sound; }
class GameOverScene : public SceneBase
{
public:
	GameOverScene(std::shared_ptr<SceneManager> manager);
	virtual ~GameOverScene();

	virtual void Initialize() final;
	virtual void Update(float deltaTime) final;
	virtual void Draw() final;

private:
	std::shared_ptr<tkl::Sound> mSndDecide;
};

#endif