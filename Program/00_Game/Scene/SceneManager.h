#pragma once

#include <memory>
#include <stack>
#include "SceneBase.h"

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	template <class T>
	void LoadScene()
	{
		mNextScene = std::make_shared<T>(shared_from_this());
		mNextScene->Initialize();
	}

	template <class T>
	void CallScene()
	{
		if(mNowScene) mPrevScene.push(mNowScene);
		LoadScene<T>();
	}

	// 元のシーンに戻る
	void ReturnScene();
	
	// シーンの更新をする
	void SceneUpdate(float deltaTime);

private:
	std::shared_ptr<SceneBase> mNextScene;
	std::shared_ptr<SceneBase> mNowScene;
	std::stack<std::shared_ptr<SceneBase>> mPrevScene;
};