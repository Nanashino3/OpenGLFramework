//****************************************************************************
// �t�@�C�����FGameOverScene(�Q�[���I�[�o��ʃN���X)
// ��@���@���F2023/1/9
#include "GameOverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Graphics/Canvas.h"

#include "../../01_Engine/Camera/ScreenCamera.h"

#include "../../02_Library/Input.h"

// �萔
static constexpr float PLAY_BTN_HEIGHT = 64.0f;
static constexpr float EXIT_BTN_HEIGHT = 128.0f;

GameOverScene::GameOverScene()
: m2DCam(nullptr)
, mCanvas(nullptr)
{}

GameOverScene::~GameOverScene()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F������
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������������s��
//****************************************************************************
void GameOverScene::Initialize()
{
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// UI�`��ƃ{�^���̐���
	mCanvas = std::make_shared<tkl::Canvas>();
	mCanvas->AddButton("Title", tkl::Vector3(0.0f, -PLAY_BTN_HEIGHT, 0.0f), [this]() {
		SceneManager::GetInstance()->LoadScene(std::make_shared<TitleScene>());
	});
	mCanvas->AddButton("Exit", tkl::Vector3(0.0f, -EXIT_BTN_HEIGHT, 0.0f), [this]() {
		exit(1);
	});
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void GameOverScene::Update(float deltaTime)
{
	m2DCam->Update();
	mCanvas->Update();
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`�揈�����s��
//****************************************************************************
void GameOverScene::Draw()
{
	tkl::Font::DrawFontEx(0.0f, 0.0f, 64, tkl::Vector3(1.0f, 0.0f, 0.0f), "GAME OVER");
	mCanvas->Draw(m2DCam);
}