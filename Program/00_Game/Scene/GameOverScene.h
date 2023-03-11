//****************************************************************************
// ファイル名：GameScene(ゲーム画面クラス)
// 作　成　日：2022/12/15
#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_

#include "SceneBase.h"
namespace tkl{ class Sound; }
class GameOverScene : public SceneBase
{
public:
	GameOverScene();
	virtual ~GameOverScene();

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	std::shared_ptr<tkl::Sound> mSndDecide;
};

#endif