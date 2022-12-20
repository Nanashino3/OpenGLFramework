//****************************************************************************
// �t�@�C�����FTitleScene(�^�C�g����ʃN���X)
// ��@���@���F2022/12/15
#include "TitleScene.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../02_Library/Input.h"

TitleScene::TitleScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{
	mSndDecide = tkl::Sound::CreateSound("Resource/sound/decide.wav");
}

TitleScene::~TitleScene()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F������
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������������s��
//****************************************************************************
void TitleScene::Initialize()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void TitleScene::Update(float deltaTime)
{
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_ENTER)){
		mSceneManager->LoadScene<GameScene>();
		mSndDecide->Play();
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`�揈�����s��
//****************************************************************************
void TitleScene::Draw()
{
	tkl::Font::DrawStringEx(0, 0, "�^�C�g�����");
}