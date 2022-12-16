//****************************************************************************
// �t�@�C�����FSceneManager(��ʊǗ��N���X)
// ��@���@���F2022/12/15
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
	
	//****************************************************************************
	// �֐����FLoadScene
	// �T�@�v�F��ʂ̓ǂݍ���
	// ���@���F�Ȃ�
	// �߂�l�F�Ȃ�
	// �ځ@�ׁF�w�肵���V������ʂ�ǂݍ���
	//****************************************************************************
	template <class T>
	void LoadScene()
	{
		while(!mPrevScene.empty()){ mPrevScene.pop(); }
		mNextScene = std::make_shared<T>(shared_from_this());
		mNextScene->Initialize();
	}

	//****************************************************************************
	// �֐����FCallScene
	// �T�@�v�F��ʂ̌Ăяo��
	// ���@���F�Ȃ�
	// �߂�l�F�Ȃ�
	// �ځ@�ׁF�w�肵����ʂ��Ăяo��(���[�_���ɋ߂�)
	//****************************************************************************
	template <class T>
	void CallScene()
	{
		if(mNowScene) mPrevScene.push(mNowScene);
		mNextScene = std::make_shared<T>(shared_from_this());
		mNextScene->Initialize();
	}

	// ���̃V�[���ɖ߂�
	void ReturnScene();
	
	// �V�[���̍X�V������
	void SceneUpdate(float deltaTime);

private:
	std::shared_ptr<SceneBase> mNextScene;
	std::shared_ptr<SceneBase> mNowScene;
	std::stack<std::shared_ptr<SceneBase>> mPrevScene;
};

#endif