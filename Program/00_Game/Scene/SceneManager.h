#pragma once

#include <memory>
#include "SceneBase.h"

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	template <class T>
	void LoadScene()
	{
		mScene = std::make_shared<T>(shared_from_this());
		mScene->Initialize();
	}

	void SceneUpdate(float deltaTime);

private:
	std::shared_ptr<SceneBase> mScene;
};