#pragma once

#include <memory>
#include <stack>
#include "SceneBase.h"

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	// �S�ẴV�[�����폜���ǉ�����
	template <class T>
	void LoadScene()
	{
		mScene = std::make_shared<T>(shared_from_this());
		mScene->Initialize();
		mSceneList.push(mScene);
	}

	// ���̃V�[���ɖ߂�
	void ReturnScene();
	
	// �V�[���̍X�V������
	void SceneUpdate(float deltaTime);

private:
	std::shared_ptr<SceneBase> mScene;
	std::stack<std::shared_ptr<SceneBase>> mSceneList;
};