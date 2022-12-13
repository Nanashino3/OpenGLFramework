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

DefenseUnit::DefenseUnit(std::shared_ptr<GameParameter> param)
: mMesh(nullptr)
{
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_water.bmp"));

	tkl::Vector3 clickPos = param->GetClickPos();
	mMesh->SetPosition(tkl::Vector3(clickPos.mX, 12.5f, clickPos.mZ));
}

DefenseUnit::~DefenseUnit()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�h�q���j�b�g�N���X�̍X�V����
//****************************************************************************
void DefenseUnit::Update(std::shared_ptr<GameParameter>& param)
{
	// ���g(�h�q���j�b�g)��`��
	mMesh->Draw(param->GetCamera());
	
	// �������Ă��Ȃ��ꍇ�͒e����
	if (!mBullet.expired()) { return; }
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	if (list.size() != 0) {
		tkl::Vector3 nearPos;
		for (auto it = list.begin(); it != list.end(); ++it) {
			std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);
			tkl::Vector3 pos = unit->GetUnitPosition();
			float distance = tkl::Vector3::Distance(pos, mMesh->GetPosition());
			if (distance <= 55.0f) { nearPos = pos; break; }
		}
		if (tkl::Vector3::Magnitude(nearPos) == 0) { return; }

		// �e�֘A����
		mBullet = ObjectManager::GetInstance()->Create<Bullet>(param);
		std::shared_ptr<Bullet> bullet = mBullet.lock();
		bullet->SetLauncherPos(mMesh->GetPosition());
		bullet->SetTargetPos(nearPos);
		bullet->Preparation();
	}
}