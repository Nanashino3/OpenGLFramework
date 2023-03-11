//****************************************************************************
// �t�@�C�����FSceneManager(��ʊǗ��N���X)
// ��@���@���F2022/12/15
#include "SceneManager.h"
#include "../../02_Library/Utility.h"

SceneManager* SceneManager::sMyInstance = nullptr;
SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

SceneManager* SceneManager::GetInstance()
{
	if(!sMyInstance){ sMyInstance = new SceneManager(); }
	return sMyInstance;
}

void SceneManager::DestoryInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// �֐����FLoadScene
// �T�@�v�F��ʂ̓ǂݍ���
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�w�肵���V������ʂ�ǂݍ���
//****************************************************************************
void SceneManager::LoadScene(std::shared_ptr<SceneBase> nextScene)
{
	while (!mPrevScene.empty()){ mPrevScene.pop(); }
	mNextScene = nextScene;
	mNextScene->Initialize();
}

//****************************************************************************
// �֐����FCallScene
// �T�@�v�F��ʂ̌Ăяo��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�w�肵����ʂ��Ăяo��(���[�_���ɋ߂�)
//****************************************************************************
void SceneManager::CallScene(std::shared_ptr<SceneBase> nextScene)
{
	if (mNowScene){ mPrevScene.push(mNowScene); }
	mNextScene = nextScene;
	mNextScene->Initialize();
}

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
	if(mNextScene != nullptr){
		if(mNowScene != mNextScene){
			mNowScene = mNextScene;
			mNextScene = nullptr;
		}
	}

	if(!mPrevScene.empty()){
		std::shared_ptr<SceneBase> prevScene = mPrevScene.top();
		prevScene->Draw();
	}

	// ���݂̃V�[���̏���
	mNowScene->Update(deltaTime);
	mNowScene->Draw();
}