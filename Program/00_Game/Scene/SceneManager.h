#pragma once

#include <memory>
#include <stack>
#include "SceneBase.h"

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	// 全てのシーンを削除し追加する
	template <class T>
	void LoadScene()
	{
		mScene = std::make_shared<T>(shared_from_this());
		mScene->Initialize();
		mSceneList.push(mScene);
	}

	// 元のシーンに戻る
	void ReturnScene();
	
	// シーンの更新をする
	void SceneUpdate(float deltaTime);

private:
	std::shared_ptr<SceneBase> mScene;
	std::stack<std::shared_ptr<SceneBase>> mSceneList;
};