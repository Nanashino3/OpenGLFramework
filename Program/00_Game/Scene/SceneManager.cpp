//****************************************************************************
// �t�@�C�����FSceneManager(��ʊǗ��N���X)
// ��@���@���F2022/12/15
#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

//****************************************************************************
// �֐����FReturnScene
// �T�@�v�F��ʂ�߂�
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�J�ڑO�̉�ʂɖ߂�
//****************************************************************************
void SceneManager::ReturnScene()
{
	if(mPrevScene.empty()){ return; }
	mNextScene = mPrevScene.top();
	mPrevScene.pop();
}

//****************************************************************************
// �֐����FSceneUpdate
// �T�@�v�F��ʂ̍X�V
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF��ʂ̍X�V���s��
//****************************************************************************
void SceneManager::SceneUpdate(float deltaTime)
{
	// �V�[���̃C���X�^���X���X�V
	if(mNowScene != mNextScene){ mNowScene = mNextScene; }

	if(!mPrevScene.empty()){
		auto prevScene = mPrevScene.top();
		prevScene->Draw();
	}

	// ���݂̃V�[���̏���
	mNowScene->Update(deltaTime);
	mNowScene->Draw();
}