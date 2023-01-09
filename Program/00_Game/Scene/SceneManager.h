//****************************************************************************
// ファイル名：SceneManager(画面管理クラス)
// 作　成　日：2022/12/15
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <memory>
#include <stack>
#include "SceneBase.h"

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
	
	void LoadScene(std::shared_ptr<SceneBase> nextScene);
	void CallScene(std::shared_ptr<SceneBase> nextScene);
	void ReturnScene();
	void SceneUpdate(float deltaTime);

private:
	std::shared_ptr<SceneBase> mNextScene;
	std::shared_ptr<SceneBase> mNowScene;
	std::stack<std::shared_ptr<SceneBase>> mPrevScene;
};

#endif