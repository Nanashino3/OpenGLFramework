//****************************************************************************
// �t�@�C�����FBullet(�e�N���X)
// ��@���@���F2022/12/6
#include "Bullet.h"

#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"

// TODO�F�萔�͂ǂ����ɂ܂Ƃ߂�H
const int BULLET_SIZE = 5;
const float DESTROY_POS = 70.0f;

Bullet::Bullet(std::shared_ptr<GameParameter> param)
: mRadian(0)
, mMesh(nullptr)
{
	mMesh = tkl::Mesh::CreateSphere(BULLET_SIZE, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
}

Bullet::~Bullet()
{}

//****************************************************************************
// �֐����FPreparation
// �T�@�v�F���O����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N���X�̎��O�������s��
//****************************************************************************
void Bullet::Preparation()
{
	tkl::Vector3 diff = mTargetPos - mLauncherPos;
	mRadian = atan2f(diff.mZ, diff.mX);

	mMesh->SetPosition(mLauncherPos);
}

//****************************************************************************
// �֐����FCollision
// �T�@�v�F�Փ˔���
// ���@���F
// �߂�l�F
// �ځ@�ׁF�e�N���X�̏Փ˔���
//****************************************************************************
void Bullet::Collision()
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// �i�R���j�b�g���X�g���擾
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	for(auto it = list->begin(); it != list->end(); ++it){
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);		
		tkl::Vector3 unitPos = unit->GetUnitPosition();

		// �i�R���j�b�g�ƏՓ˂��Ă�����e�폜
		if(tkl::IsIntersectAABB(pos, 12.5f, unitPos, 5.0f)){
			mIsAlive = false;
			// TODO�F�^����_���[�W�͉ςɂ�����
			unit->ReceiveDamage(10);
			break; 
		}
	}
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N���X�̍X�V����
//****************************************************************************
void Bullet::Update(std::shared_ptr<GameParameter>& param)
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// �i�ޕ����v�Z
	pos.mX += cosf(mRadian) * 50.0f * param->GetDeltaTime();
	pos.mZ += sinf(mRadian) * 50.0f * param->GetDeltaTime();

	// ��苗���܂ōs������e�폜
	float d = tkl::Vector3::Distance(mLauncherPos, pos);
	if (d > DESTROY_POS) { mIsAlive = false; }

	mMesh->SetPosition(pos);
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N���X�̕`�揈��
//****************************************************************************
void Bullet::Draw(std::shared_ptr<GameParameter>& param)
{
	mMesh->Draw(param->GetCamera());
}