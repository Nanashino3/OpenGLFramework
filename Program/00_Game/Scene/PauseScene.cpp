//****************************************************************************
// �t�@�C�����FPauseScene(�|�[�Y��ʃN���X)
// ��@���@���F2022/12/15
#include "PauseScene.h"

#include "SceneManager.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../02_Library/Input.h"

PauseScene::PauseScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{
	mSndCancel = tkl::Sound::CreateSound("Resource/sound/cancel.wav");
}

PauseScene::~PauseScene()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F������
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������������s��
//****************************************************************************
void PauseScene::Initialize()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void PauseScene::Update(float deltaTime)
{
	// �O�̃V�[���ɖ߂�
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_P)){
		mSceneManager->ReturnScene();
		mSndCancel->Play();
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`�揈�����s��
//****************************************************************************
void PauseScene::Draw()
{
	tkl::Font::DrawStringEx(0, 0, "�|�[�Y���");
}