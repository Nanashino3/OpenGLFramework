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
#include "../../01_Engine/Font.h"
#include "../../01_Engine/Camera/FixedCamera.h"
#include "../../02_Library/Input.h"
#include "../../02_Library/Utility.h"

GameScene::GameScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
, mElapsed(0)
, mDurability(MAX_DURABILITY)
, mParam(nullptr)
, mCamera(nullptr)
, mField(nullptr)
{}

GameScene::~GameScene()
{
	ObjectManager::GetInstance()->DestroyInstance();
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
	mCamera = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	mCamera->SetPosition(tkl::Vector3(0, 400, 200));

	// �p�����[�^����
	mParam = std::make_shared<GameParameter>();
	mParam->SetCamera(mCamera);

	// �t�B�[���h����
	mField = std::make_shared<Field>(mParam);

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
		return;
	}
	tkl::Font::DrawStringEx(0, 0, "�Q�[�����");

	// �J�����X�V
	mCamera->Update();
	mParam->SetDeltaTime(deltaTime);

	if (mParam->GetIsArrival()) {
		if (mDurability != 0) mDurability -= 1;
		mParam->SetIsArrival(false);
	}

	// �i�R���j�b�g
	mElapsed += deltaTime;
	if (mElapsed > 5.0f) {
		mElapsed = 0;

		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		if (list->size() != MAX_CREATE) {
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
	tkl::Font::DrawStringEx(0, 50, "�ϋv�x : %d", mDurability);
	tkl::Font::DrawStringEx(0, 100, "�c�� : %d", mParam->GetTotalCost());
	tkl::Font::DrawStringEx(0, 150, "�i�R���x�� : %2d", mParam->GetAdvenceLevel());

	// �t�B�[���h�̍X�V
	mField->Draw();

	// �I�u�W�F�N�g�̕`�揈��
	ObjectManager::GetInstance()->Draw();
}