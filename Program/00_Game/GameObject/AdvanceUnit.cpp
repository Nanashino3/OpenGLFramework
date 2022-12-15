//****************************************************************************
// �t�@�C�����FAdvanceUnit(�i�R���j�b�g�N���X)
// ��@���@���F2022/12/4
#include "AdvanceUnit.h"

#include "GameParameter.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

AdvanceUnit::AdvanceUnit(std::shared_ptr<Parameter> param)
: mRouteCount(0)
, mFirstPosX(0), mFirstPosZ(0)
, mMoveSpeed(15.0f)
, mHitPoint(100)
, mMesh(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
}

AdvanceUnit::~AdvanceUnit()
{}

void AdvanceUnit::Initialize()
{
	int mapSize = mParam->GetMapSize();
	int mapRow = mParam->GetMapRow();
	int mapColumn = mParam->GetMapColumn();
	auto field = mParam->GetFields();

	// �o�H����(����)
	tkl::Algorithm::RouteSearch(mapRow, mapColumn, field, mRoute);

	mRouteCount = mRoute.size() - 1;
	mMesh = tkl::Mesh::CreateBox(25);

	// �������W�v�Z
	mFirstPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	mFirstPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	mMesh->SetPosition(tkl::Vector3(mFirstPosX, (mapSize >> 1), mFirstPosZ));
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�i�R���j�b�g�N���X�̍X�V����
//****************************************************************************
void AdvanceUnit::Update()
{
	if (mRouteCount == 0 && mRoute[mRouteCount].status == tkl::STATUS::GOAL) {
		mIsAlive = false;
		mParam->SetIsArrival(true);
		return;
	}

	tkl::Vector3 pos = mMesh->GetPosition();
	int mapSize = mParam->GetMapSize();

	float targetPosX = mFirstPosX + mapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mapSize * mRoute[mRouteCount - 1].row;

	// �ړ��ʌv�Z
	int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	//******************************************************************
	// �T�������o�H��i�ޏ���
	pos.mX += mMoveSpeed * dx * mParam->GetDeltaTime();
	pos.mZ += mMoveSpeed * dz * mParam->GetDeltaTime();

	if(dx > 0 || dz > 0){
		if(pos.mX > targetPosX || pos.mZ > targetPosZ){
			pos.mX = targetPosX; pos.mZ = targetPosZ;
			if(mRouteCount > 0) mRouteCount--;
		}
	}else if(dx < 0 || dz < 0){
		if(pos.mX < targetPosX || pos.mZ < targetPosZ){
			pos.mX = targetPosX; pos.mZ = targetPosZ;
			if(mRouteCount > 0) mRouteCount--;
		}
	}
	//******************************************************************

	mMesh->SetPosition(pos);
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�i�R���j�b�g�N���X�̕`�揈��
//****************************************************************************
void AdvanceUnit::Draw()
{
	mMesh->Draw(mParam->GetCamera());
}

//****************************************************************************
// �֐����FReceiveDamage
// �T�@�v�F�_���[�W���󂯂�
// ���@���Farg1 �󂯂�_���[�W��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�_���[�W�̏���������(TODO�F�����Ƃ������@������΍��ς���)
//****************************************************************************
void AdvanceUnit::ReceiveDamage(int damage)
{
	mHitPoint -= damage;
	if(mHitPoint < 0){
		mIsAlive = false;
		mParam->SetTotalCost( mParam->GetTotalCost() + 25 );
	}
}

//****************************************************************************
// �֐����FGetUnitPosition
// �T�@�v�F���j�b�g�ʒu���擾
// ���@���F�Ȃ�
// �߂�l�F���j�b�g�̈ʒu
// �ځ@�ׁF�i�R���j�b�g���g�̈ʒu��Ԃ�
//****************************************************************************
tkl::Vector3 AdvanceUnit::GetUnitPosition() const
{
	return mMesh->GetPosition();
}

//****************************************************************************
// �֐����FSetNewRoute(private)
// �T�@�v�F�ŐV���[�g�ݒ�
// ���@���Farg1 �ŐV���[�g
// �߂�l�F�Ȃ�
// �ځ@�ׁF�ŐV�̃��[�g��ݒ肷��
//****************************************************************************
void AdvanceUnit::SetNewRoute(const std::vector<tkl::CELL>& newRoute)
{
	int prevSize = mRoute.size();
	int currentSize = newRoute.size();

	mRoute = newRoute;
	mRouteCount = mRouteCount + abs(prevSize - currentSize);
}