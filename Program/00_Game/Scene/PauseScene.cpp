//****************************************************************************
// �t�@�C�����FPauseScene(�|�[�Y��ʃN���X)
// ��@���@���F2022/12/15
#include "PauseScene.h"

#include "SceneManager.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../02_Library/Input.h"

// �t�@�C���p�X
static constexpr const char* SOUND_FILE = "Resource/sound/cancel.wav";

PauseScene::PauseScene()
: mSndCancel(nullptr)
{}

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
{
	mSndCancel = tkl::Sound::CreateSound(SOUND_FILE);
}

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
		mSndCancel->Play();
		SceneManager::GetInstance()->ReturnScene();
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
	tkl::Font::DrawFontEx(0, 0, 32, tkl::Vector3(1, 1, 1), "PAUSED");
}