//****************************************************************************
// �t�@�C�����FDefenseUnit(�h�q���j�b�g�N���X)
// ��@���@���F2022/12/5
#include "DefenseUnit.h"

#include "Bullet.h"
#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"

#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"

#include "../../02_Library/Math.h"

// �t�@�C���p�X
static constexpr const char* MODEL_FILE = "Resource/Model/Turret/1/Turret.obj";
static constexpr const char* SOUND_FILE = "Resource/sound/shot.wav";

// �萔
static constexpr int CONSUME_COST = 75;
static constexpr float MODEL_SCALE = 15;
static constexpr float DIST_MAX = 70.0f;
static constexpr float CREATE_INTERVAL = 0.8f;

DefenseUnit::DefenseUnit(std::shared_ptr<Parameter> param)
: mElapsedTime(0.0f)
, mModel(nullptr)
, mSound(nullptr)
, mParam(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);	
}

DefenseUnit::~DefenseUnit()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�h�q���j�b�g�N���X�̏���������
//****************************************************************************
void DefenseUnit::Initialize()
{
	mSound = tkl::Sound::CreateSound(SOUND_FILE);

	tkl::Vector3 clickPos = mParam->GetClickPos();

	mModel = tkl::Model::CreateModelFromObjFile(MODEL_FILE);
	mModel->SetPosition(tkl::Vector3(clickPos));
	mModel->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(90)));
	mModel->SetScale(tkl::Vector3(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

	mParam->SetTotalCost(mParam->GetTotalCost() - CONSUME_COST);
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�h�q���j�b�g�N���X�̍X�V����
//****************************************************************************
void DefenseUnit::Update()
{
	tkl::Quaternion rot = mModel->GetRotation();
	tkl::Vector3 modelPos = mModel->GetPosition();

	// 1�ԋ߂��i�R���j�b�g��T��
	tkl::Vector3 nearPos;
	const std::list<std::shared_ptr<GameObject>>* list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	for(auto iter = list->begin(); iter != list->end(); ++iter){
		std::shared_ptr<AdvanceUnit> unit = std::dynamic_pointer_cast<AdvanceUnit>(*iter);
		tkl::Vector3 unitPos = unit->GetPosition();

		float dist = tkl::Vector3::Distance(unitPos, modelPos);
		if(dist <= DIST_MAX){
			// �i�R���j�b�g�̕����Ɍ���
			nearPos = tkl::Vector3(unitPos.mX, 0.0f, unitPos.mZ);
			tkl::Vector3 dir = nearPos - modelPos;
			float theta = tkl::ToDegree(std::atan2f(dir.mX, dir.mZ));
			rot = tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(-theta));
			break;
		}
	}

	// �e������
	Shoot(nearPos);

	mModel->SetRotation(rot);
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�h�q���j�b�g�N���X�̕`�揈��
//****************************************************************************
void DefenseUnit::Draw()
{
	mModel->Draw(mParam->GetCamera());
}

//****************************************************************************
// �֐����FShoot
// �T�@�v�F�e������
// ���@���Farg1 �ڕW�ʒu
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e��������(�e�������ǂ��������f����)
//****************************************************************************
void DefenseUnit::Shoot(const tkl::Vector3& targetPos)
{
	// �e�������Ă���ΐV������������
	if(!mBullet.expired() || (tkl::Vector3::Magnitude(targetPos) == 0)){ return; }

	// �e�����ł��Ă���b��ɔ��˂���
	// TODO�F�C���^�[�o���͉ςɂ�����
	mElapsedTime += mParam->GetDeltaTime();
	if(mElapsedTime > CREATE_INTERVAL){
		mElapsedTime = 0.0f;

		// �e�֘A����
		mBullet = ObjectManager::GetInstance()->Create<Bullet>(mParam);
		std::shared_ptr<Bullet> bullet = mBullet.lock();
		bullet->Initialize(mModel->GetPosition(), targetPos);

		mSound->Play();
	}
}