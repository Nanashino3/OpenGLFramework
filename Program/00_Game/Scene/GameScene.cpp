//****************************************************************************
// �t�@�C�����FGameScene(�Q�[����ʃN���X)
// ��@���@���F2022/12/15
#include "GameScene.h"

#include "PauseScene.h"
#include "SceneManager.h"

#include "../Field.h"
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

GameScene::GameScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
, mCamera(nullptr)
, mElapsed(0)
{}

GameScene::~GameScene()
{}

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

	// �t�B�[���h����
	mField = std::make_shared<Field>(mParam);

	// �I�u�U�[�o�[�o�^
	Notifier::GetInstance()->AddObserver(std::make_shared<AdvanceUnitObserver>());
	Notifier::GetInstance()->AddObserver(std::make_shared<DefenseUnitObserver>());

	mEndurance = 1;
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
	if(mEndurance == 0){ return; }

	// �J�����X�V
	mCamera->Update();
	mParam->SetCamera(mCamera);
	mParam->SetDeltaTime(deltaTime);

	tkl::Font::DrawStringEx(0, 100, "�ϋv�l�F%d", mEndurance);
	if (mParam->GetIsArrival()) {
		if (mEndurance != 0) mEndurance -= 1;
		mParam->SetIsArrival(false);
	}

	// �i�R���j�b�g
	mElapsed += deltaTime;
	tkl::Font::DrawStringEx(0, 50, "DeltaTime�F%f", deltaTime);

	if (mElapsed > 5.0f) {
		mElapsed = 0;

		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		if (list->size() != CREATE_MAX) {
			// �i�R���j�b�g����
			ObjectManager::GetInstance()->Create<AdvanceUnit>(mParam);
		}
	}

	// �t�B�[���h�̍X�V
	mField->Update(mParam);

	// �I�u�W�F�N�g�̏Փ˔���
	ObjectManager::GetInstance()->Collision();
	// �I�u�W�F�N�g�̍X�V����
	ObjectManager::GetInstance()->Update(mParam);

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
	tkl::Font::DrawStringEx(0, 0, "�Q�[�����");

	// �t�B�[���h�̍X�V
	mField->Draw(mParam);

	// �I�u�W�F�N�g�̕`�揈��
	ObjectManager::GetInstance()->Draw(mParam);
}