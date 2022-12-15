//****************************************************************************
// �t�@�C�����FGameManager(�Q�[���Ǘ��҃N���X)
// ��@���@���F2022/10/6
#include "GameManager.h"

#include "Scene/TitleScene.h"
#include "Scene/SceneManager.h"
#include "../02_Library/Utility.h"

GameManager* GameManager::sMyInstance = nullptr;
GameManager::GameManager()
{
	mSceneManager = std::make_shared<SceneManager>();
	mSceneManager->LoadScene<TitleScene>();
}

GameManager::~GameManager()
{}

GameManager* GameManager::GetInstance()
{
	if(!sMyInstance) sMyInstance = new GameManager();
	return sMyInstance;
}
void GameManager::DestoryInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void GameManager::Update(float deltaTime)
{
	mSceneManager->SceneUpdate(deltaTime);
}