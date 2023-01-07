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

// �t�@�C���p�X
static constexpr const char* TEXTURE_FILE = "Resource/texture/panel_concrete.bmp";

// �萔
static constexpr int BULLET_SIZE = 2;
static constexpr int DIVISION_W = 24;
static constexpr int DIVISION_H = 16;
static constexpr int DAMAGE = 5;
static constexpr float OBJECT_HEIGHT = 9.5f;
static constexpr float DESTROY_POS = 70.0f;
static constexpr float MOVE_SPEED = 100.0f;
static constexpr float RECT_SIZE = 8.5f;

Bullet::Bullet(std::shared_ptr<Parameter> param)
: mRadian(0)
, mMesh(nullptr)
, mParam(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
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
void Bullet::Initialize(const tkl::Vector3& srcPos, const tkl::Vector3& target)
{
	tkl::Vector3 diff = target - srcPos;
	mRadian = atan2f(diff.mZ, diff.mX);
	mLauncherPos = srcPos;

	mMesh = tkl::Mesh::CreateSphere(BULLET_SIZE, DIVISION_W, DIVISION_H);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));
	mMesh->SetPosition(tkl::Vector3(srcPos.mX, OBJECT_HEIGHT, srcPos.mZ));
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
	const std::list<std::shared_ptr<GameObject>>* list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	for(auto it = list->begin(); it != list->end(); ++it){
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);		
		tkl::Vector3 unitPos = unit->GetPosition();

		// �i�R���j�b�g�ƏՓ˂��Ă�����e�폜
		// TODO�F�i�R���j�b�g�̃T�C�Y���擾�ł���悤�ɂ���
		if(tkl::IsIntersectAABB(pos, BULLET_SIZE, unitPos, RECT_SIZE)){
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