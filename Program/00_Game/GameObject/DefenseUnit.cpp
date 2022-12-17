//****************************************************************************
// �t�@�C�����FDefenseUnit(�h�q���j�b�g�N���X)
// ��@���@���F2022/12/5
#include "DefenseUnit.h"

#include "Bullet.h"
#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

DefenseUnit::DefenseUnit(std::shared_ptr<Parameter> param)
: mMesh(nullptr)
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
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_water.bmp"));

	tkl::Vector3 clickPos = mParam->GetClickPos();
	mMesh->SetPosition(tkl::Vector3(clickPos.mX, 12.5f, clickPos.mZ));

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
	if (!mBullet.expired()) { return; }

	// �������Ă��Ȃ��ꍇ�͒e����
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	tkl::Vector3 nearPos;
	for (auto it = list->begin(); it != list->end(); ++it) {
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);
		tkl::Vector3 pos = unit->GetUnitPosition();
		float dist = tkl::Vector3::Distance(pos, mMesh->GetPosition());
		if (dist <= CREATE_DISTANCE) { nearPos = pos; break; }
	}
	if (tkl::Vector3::Magnitude(nearPos) == 0) { return; }

	// �e�֘A����
	mBullet = ObjectManager::GetInstance()->Create<Bullet>(mParam);
	std::shared_ptr<Bullet> bullet = mBullet.lock();
	bullet->SetLauncherPos(mMesh->GetPosition());
	bullet->SetTargetPos(nearPos);
	bullet->Initialize();
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
	mMesh->Draw(mParam->GetCamera());
}