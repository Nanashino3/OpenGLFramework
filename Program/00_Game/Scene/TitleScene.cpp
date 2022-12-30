//****************************************************************************
// �t�@�C�����FTitleScene(�^�C�g����ʃN���X)
// ��@���@���F2022/12/15
#include "TitleScene.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "../../01_Engine/System.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Font.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Camera/ScreenCamera.h"
#include "../../02_Library/Input.h"

static constexpr const char* DECIDE_FILE = "Resource/sound/decide.wav";
static constexpr const char* TEXTURE_FILE = "Resource/texture/img_title.jpg";

TitleScene::TitleScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{
	mSndDecide = tkl::Sound::CreateSound(DECIDE_FILE);
	mTexMesh = tkl::Mesh::CreateMeshForSprite();
	mTexMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));

	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	mCamera = std::make_shared<tkl::ScreenCamera>(screenW, screenH);
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
	mCamera->Update();

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
	mTexMesh->Draw(mCamera);
	tkl::Font::DrawStringEx(0, 0, tkl::Vector3(1, 1, 1), "�^�C�g�����");
}