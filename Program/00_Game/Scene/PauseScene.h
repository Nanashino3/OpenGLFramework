//****************************************************************************
// ファイル名：PauseScene(ポーズ画面クラス)
// 作　成　日：2022/12/15
#ifndef _PAUSESCENE_H_
#define _PAUSESCENE_H_

#include "SceneBase.h"
class PauseScene : public SceneBase
{
public:
	PauseScene(std::shared_ptr<SceneManager> manager);
	virtual ~PauseScene();

	virtual void Initialize() final;
	virtual void Update(float deltaTime) final;
	virtual void Draw() final;
};

#endif