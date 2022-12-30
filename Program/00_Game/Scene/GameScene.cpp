//****************************************************************************
// �t�@�C�����FGameScene(�Q�[����ʃN���X)
// ��@���@���F2022/12/15
#include "GameScene.h"

#include "PauseScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"

#include "../Field.h"
#include "../GameObject/Cell.h"
#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/GameParameter.h"
#include "../GameObject/ObjectManager.h"

#include "../NotifyService/Notifier.h"
#include "../NotifyService/AdvanceUnitObserver.h"
#include "../NotifyService/DefenseUnitObserver.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Camera/FixedCamera.h"
#include "../../01_Engine/Camera/ScreenCamera.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Graphics/Font.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Utility.h"

static constexpr int MAX_CREATE = 5;
static constexpr int MAX_DURABILITY = 1;
static constexpr const char* BGM_FILE = "Resource/sound/gamebgm.wav";
static constexpr const char* PAUSE_SE_FILE = "Resource/sound/pause.wav";

GameScene::GameScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
, mElapsed(0)
, mDurability(MAX_DURABILITY)
, mParam(nullptr)
, m3DCam(nullptr), m2DCam(nullptr)
, mbgTex(nullptr)
, mField(nullptr)
, mSndBgm(nullptr)
{
	mSndBgm = tkl::Sound::CreateSound(BGM_FILE);
	mSndPause = tkl::Sound::CreateSound(PAUSE_SE_FILE);
}

GameScene::~GameScene()
{
	ObjectManager::GetInstance()->DestroyInstance();
	Notifier::GetInstance()->DestroyInstance();
}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F������
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������������s��
//****************************************************************************
void GameScene::Initialize()
{
	// �E�B���h�E�T�C�Y���擾
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);

	// 3D�J��������
	m3DCam = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	m3DCam->SetPosition(tkl::Vector3(0, 350, 180));

	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// �p�����[�^����
	mParam = std::make_shared<GameParameter>();
	mParam->SetCamera(m3DCam);

	// �t�B�[���h����
	mField = std::make_shared<Field>(mParam);

	mbgTex = tkl::Mesh::CreateMeshForSprite();
	mbgTex->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/img_play.jpg"));

	// �I�u�U�[�o�[�o�^
	Notifier::GetInstance()->AddObserver(std::make_shared<AdvanceUnitObserver>());
	Notifier::GetInstance()->AddObserver(std::make_shared<DefenseUnitObserver>());
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void GameScene::Update(float deltaTime)
{
	// TODO�F�b��őϋv��݂���
	if(mDurability == 0){
		mSceneManager->CallScene<GameOverScene>();
		mSndBgm->Stop();
		return;
	}
	if(!mSndBgm->IsPlay()){ mSndBgm->Play(); }

	// �J�����X�V
	m3DCam->Update();
	m2DCam->Update();
	mParam->SetDeltaTime(deltaTime);

	if(mParam->GetIsArrival()){
		if(mDurability != 0){ mDurability -= 1; }
		mParam->SetIsArrival(false);
	}

	// �i�R���j�b�g
	mElapsed += deltaTime;
	if(mElapsed > 5.0f){
		mElapsed = 0;

		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		if(list->size() != MAX_CREATE){
			// �i�R���j�b�g����
			auto newUnit = ObjectManager::GetInstance()->Create<AdvanceUnit>(mParam);
			newUnit->Initialize();
		}
	}

	// �t�B�[���h�̍X�V
	mField->Update();

	// �I�u�W�F�N�g�̏Փ˔���
	ObjectManager::GetInstance()->Collision();

	// �I�u�W�F�N�g�̍X�V����
	ObjectManager::GetInstance()->Update();

	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_P)){
		mSceneManager->CallScene<PauseScene>();
		mSndPause->Play();
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`�揈�����s��
//****************************************************************************
void GameScene::Draw()
{
	mbgTex->Draw(m2DCam);

	tkl::Font::DrawStringEx(0,   0, tkl::Vector3(1, 1, 1), "�ϋv�x : %d", mDurability);
	tkl::Font::DrawStringEx(0,  50, tkl::Vector3(1, 1, 1), "�c�� : %d", mParam->GetTotalCost());
	tkl::Font::DrawStringEx(0, 100, tkl::Vector3(1, 1, 1), "�i�R���x�� : %2d", mParam->GetAdvenceLevel());

	// �t�B�[���h�̍X�V
	mField->Draw();

	// �I�u�W�F�N�g�̕`�揈��
	ObjectManager::GetInstance()->Draw();
}