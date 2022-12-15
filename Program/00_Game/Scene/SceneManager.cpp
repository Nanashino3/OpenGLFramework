#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

void SceneManager::ReturnScene()
{
	if(mPrevScene.empty()) return ;
	mNextScene = mPrevScene.top();
	mPrevScene.pop();
}

void SceneManager::SceneUpdate(float deltaTime)
{
	// �V�[���̃C���X�^���X���X�V
	if(mNowScene != mNextScene){ mNowScene = mNextScene; }

	// ���݂̃V�[���̏���
	mNowScene->Update(deltaTime);
	mNowScene->Draw();

	if(mPrevScene.empty()){ return; }
	
	auto prevScene = mPrevScene.top();
	prevScene->Draw();
}