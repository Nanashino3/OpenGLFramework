#include "PlayScene.h"

#include "../Field.h"
#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/GameParameter.h"
#include "../GameObject/ObjectManager.h"
#include "../NotifyService/Notifier.h"
#include "../NotifyService/AdvanceUnitObserver.h"
#include "../NotifyService/DefenseUnitObserver.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/FixedCamera.h"
#include "../../01_Engine/Font.h"

const int CREATE_MAX = 5;

PlayScene::PlayScene()
: mCamera(nullptr)
, mElapsed(0)
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
}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	tkl::Font::DrawStringEx(0, 0, "�v���C�V�[��");

	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	// �J�����X�V
	mCamera->Update();
	mParam->SetCamera(mCamera);
	mParam->SetDeltaTime(deltaTime);

	// �t�B�[���h�̍X�V
	mField->Update(mParam);

//	//******************************************************************
//	// TODO�F�ŒZ�o�H�\���p(�f�o�b�O�Ƃ��ČĂяo������)
//	for(int i = 0; i < mRoute.size(); ++i){
//		std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(SIZE);
//
//		float posX = mFirstPosX + SIZE * mRoute[i].column;
//		float posZ = mFirstPosZ + SIZE * mRoute[i].row;
//		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
//		mesh->SetPosition(tkl::Vector3(posX, 0, posZ));
//		mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
//		mesh->Draw(mCamera);
//	}
	
	//******************************************************************
	// �i�R���j�b�g
	mElapsed += deltaTime;
	tkl::Font::DrawStringEx(0, 50, "DeltaTime�F%f", deltaTime);

	if (mElapsed > 5.0f){
		mElapsed = 0;

		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		if(list.size() != CREATE_MAX){
			// �i�R���j�b�g����
			ObjectManager::GetInstance()->Create<AdvanceUnit>(mParam);
		}
	}

	//******************************************************************
	// �I�u�W�F�N�g�`��
	ObjectManager::GetInstance()->Update(mParam);

	return nextScene;
}