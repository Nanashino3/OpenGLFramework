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
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Utility.h"

#include "../Graphics/Ui/UiBase.h"
#include "../Graphics/Ui/UiHitPoint.h"

// �t�@�C���p�X
static constexpr const char* BGM_FILE = "Resource/sound/gamebgm.wav";
static constexpr const char* PAUSE_SE_FILE = "Resource/sound/pause.wav";
static constexpr const char* BG_TEXTURE = "Resource/texture/img_play.jpg";

// �萔
static constexpr int MAX_CREATE = 2;
static constexpr int MAX_DURABILITY = 1;
static constexpr float CREATE_INTERVAL = 5.0f;
static constexpr float CAMERA_POS_Y = 250.0f;
static constexpr float CAMERA_POS_Z = 200.0f;

GameScene::GameScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
, mDurability(MAX_DURABILITY)
, mElapsedTime(0.0f)
, mField(nullptr)
, mParam(nullptr)
, m3DCam(nullptr), m2DCam(nullptr)
, mbgTex(nullptr)
, mSndBgm(nullptr), mSndPause(nullptr)
{}

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
	mSndBgm = tkl::Sound::CreateSound(BGM_FILE);
	mSndPause = tkl::Sound::CreateSound(PAUSE_SE_FILE);

	// �E�B���h�E�T�C�Y���擾
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);

	// 3D�J��������
	m3DCam = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	m3DCam->SetPosition(tkl::Vector3(0.0f, CAMERA_POS_Y, CAMERA_POS_Z));

	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// �p�����[�^����
	mParam = std::make_shared<GameParameter>();
	mParam->SetCamera(m3DCam);

	// �t�B�[���h����
	mField = std::make_shared<Field>(mParam);

	mbgTex = tkl::Mesh::CreateMeshForSprite();
	mbgTex->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(BG_TEXTURE));

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
		mSndBgm->Stop();
		mSceneManager->CallScene(std::make_shared<GameOverScene>(mSceneManager));
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
	mElapsedTime += deltaTime;
	if(mElapsedTime > CREATE_INTERVAL){
		mElapsedTime = 0.0f;

		const std::list<std::shared_ptr<GameObject>>* list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		if(list->size() != MAX_CREATE){
			// �i�R���j�b�g����
			std::shared_ptr<AdvanceUnit> newObject = ObjectManager::GetInstance()->Create<AdvanceUnit>(mParam);
			newObject->Initialize();

			// UI�𐶐�
			std::shared_ptr<UiHitPoint> newUi = std::make_shared<UiHitPoint>();
			newUi->Initialize(newObject);
			mUiList.emplace_back(newUi);
		}
	}

	// �t�B�[���h�̍X�V
	mField->Update();

	// �I�u�W�F�N�g�̏Փ˔���
	ObjectManager::GetInstance()->Collision();

	// �I�u�W�F�N�g�̍X�V����
	ObjectManager::GetInstance()->Update();

	// UI���X�g
	for(auto it = mUiList.begin(); it != mUiList.end();){
		(*it)->Update();
		if(!(*it)->IsEnabled()){
			it = mUiList.erase(it);
			continue;
		}
		++it;
	}

	// �|�[�Y��ʂ֑J��
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_P)){
		mSndPause->Play();
		mSceneManager->CallScene(std::make_shared<PauseScene>(mSceneManager));
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
	// �w�i�̕`��
	mbgTex->Draw(m2DCam);

	tkl::Font::DrawStringEx(0.0f,   0.0f, tkl::Vector3(1.0f, 1.0f, 1.0f), "�ϋv�x : %d", mDurability);
	tkl::Font::DrawStringEx(0.0f,  50.0f, tkl::Vector3(1.0f, 1.0f, 1.0f), "�c�� : %d", mParam->GetTotalCost());
//	tkl::Font::DrawStringEx(0.0f, 100.0f, tkl::Vector3(1.0f, 1.0f, 1.0f), "�i�R���x�� : %2d", mParam->GetAdvenceLevel());

	// �t�B�[���h�̍X�V
	mField->Draw();

	// �I�u�W�F�N�g�̕`�揈��
	ObjectManager::GetInstance()->Draw();

	// GameScene�ɕK�v��UI�̕`��
	// �ϋv�x�A�R�C���A�q�b�g�|�C���g(�i�R���j�b�g)
	for(auto elem : mUiList){
		elem->Draw();
	}
}