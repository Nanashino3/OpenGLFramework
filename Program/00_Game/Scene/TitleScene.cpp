//****************************************************************************
// �t�@�C�����FTitleScene(�^�C�g����ʃN���X)
// ��@���@���F2022/12/15
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneManager.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../01_Engine/Graphics/Canvas.h"

#include "../../01_Engine/Camera/ScreenCamera.h"
#include "../../01_Engine/Camera/FixedCamera.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Math.h"

// �t�@�C���p�X
static constexpr const char* TEXTURE_FILE = "Resource/texture/img_title.jpg";
static constexpr const char* MODEL_FILE = "Resource/model/earth/earth.obj";

// �萔
static constexpr float CAMERA_POS_Z = 50.0f;
static constexpr float MODEL_SIZE = 15.0f;
static constexpr float MODEL_HEIGHT = 10.0f;
static constexpr float PLAY_BTN_HEIGHT = 64.0f;
static constexpr float EXIT_BTN_HEIGHT = 128.0f;

TitleScene::TitleScene()
: mModel(nullptr)
, mTexMesh(nullptr)
, m3DCam(nullptr), m2DCam(nullptr)
, mCanvas(nullptr)
{}

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
{
	mTexMesh = tkl::Mesh::CreateMeshForSprite();
	mTexMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));

	// �J�����֘A����
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);
	m3DCam = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	m3DCam->SetPosition(tkl::Vector3(0.0f, 0.0f, CAMERA_POS_Z));

	// UI�`��ƃ{�^���̐���
	mCanvas = std::make_shared<tkl::Canvas>();
	mCanvas->AddButton("Play", tkl::Vector3(0.0f, -PLAY_BTN_HEIGHT, 0.0f), [this]() {
		SceneManager::GetInstance()->LoadScene(std::make_shared<GameScene>());
	});
	mCanvas->AddButton("Exit", tkl::Vector3(0.0f, -EXIT_BTN_HEIGHT, 0.0f), [this]() {
		exit(1);
	});

	mModel = tkl::Model::CreateModelFromObjFile(MODEL_FILE);
	mModel->SetScale(tkl::Vector3(MODEL_SIZE, MODEL_SIZE, MODEL_SIZE));
	mModel->SetPosition(tkl::Vector3(0.0f, MODEL_HEIGHT, 0.0f));
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void TitleScene::Update(float deltaTime)
{
	m2DCam->Update();
	m3DCam->Update();
	mCanvas->Update();

	tkl::Quaternion rot = mModel->GetRotation();
	rot *= tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(0.1f));
	mModel->SetRotation(rot);
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
	mTexMesh->Draw(m2DCam);
	mModel->Draw(m3DCam);

	tkl::Font::DrawFontEx(0.0f, 192, 64, tkl::Vector3(1.0f, 1.0f, 1.0f), "SPACE");
	tkl::Font::DrawFontEx(0.0f,  64, 64, tkl::Vector3(1.0f, 1.0f, 1.0f), "DEFENDER");
	mCanvas->Draw(m2DCam);
}