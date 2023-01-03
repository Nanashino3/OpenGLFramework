//****************************************************************************
// �t�@�C�����FBullet(�e�N���X)
// ��@���@���F2022/12/6
#include "Bullet.h"

#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"

static constexpr int BULLET_SIZE = 2;
static constexpr float DESTROY_POS = 70.0f;
static constexpr float MOVE_SPEED = 100.0f;
static constexpr int DAMAGE = 5;

Bullet::Bullet(std::shared_ptr<Parameter> param)
: mRadian(0)
, mMesh(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);

	mMesh = tkl::Mesh::CreateSphere(BULLET_SIZE, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/panel_concrete.bmp"));
}

Bullet::~Bullet()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F���O����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N���X�̏���������
//****************************************************************************
//void Bullet::Initialize()
void Bullet::Initialize(const tkl::Vector3& srcPos, const tkl::Vector3& target)
{
	tkl::Vector3 diff = target - srcPos;
	mRadian = atan2f(diff.mZ, diff.mX);
	mLauncherPos = srcPos;

	mMesh->SetPosition(tkl::Vector3(srcPos.mX, 9.5f, srcPos.mZ));
}

//****************************************************************************
// �֐����FCollision
// �T�@�v�F�Փˏ���
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N���X�̏Փˏ���
//****************************************************************************
void Bullet::Collision()
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// �i�R���j�b�g���X�g���擾
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	for(auto it = list->begin(); it != list->end(); ++it){
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);		
		tkl::Vector3 unitPos = unit->GetPosition();

		// �i�R���j�b�g�ƏՓ˂��Ă�����e�폜
		if(tkl::IsIntersectAABB(pos, BULLET_SIZE, unitPos, 8.5f)){
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
// ���@���F�Ȃ�
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
	if(dist > DESTROY_POS){ mIsAlive = false; }

	mMesh->SetPosition(pos);
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�e�N���X�̕`�揈��
//****************************************************************************
void Bullet::Draw()
{
	if(mIsAlive){ mMesh->Draw(mParam->GetCamera()); }
}