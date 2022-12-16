//****************************************************************************
// ファイル名：GameScene(ゲーム画面クラス)
// 作　成　日：2022/12/15
#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_

#include "SceneBase.h"
class GameOverScene : public SceneBase
{
public:
	GameOverScene(std::shared_ptr<SceneManager> manager);
	virtual ~GameOverScene();

	virtual void Initialize() final;
	virtual void Update(float deltaTime) final;
	virtual void Draw() final;
};

#endif