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

Bullet::Bullet(std::shared_ptr<Parameter> param)
: mRadian(0)
, mMesh(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);

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
void Bullet::Initialize()
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
			unit->ReceiveDamage(DAMAGE);
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
void Bullet::Update()
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// �i�ޕ����v�Z
	pos.mX += cosf(mRadian) * MOVE_SPEED * mParam->GetDeltaTime();
	pos.mZ += sinf(mRadian) * MOVE_SPEED * mParam->GetDeltaTime();

	// ��苗���܂ōs������e�폜
	float dist = tkl::Vector3::Distance(mLauncherPos, pos);
	if (dist > DESTROY_POS) { mIsAlive = false; }

	mMesh->SetPosition(pos);
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N���X�̕`�揈��
//****************************************************************************
void Bullet::Draw()
{
	mMesh->Draw(mParam->GetCamera());
}