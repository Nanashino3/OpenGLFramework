//****************************************************************************
// �t�@�C�����FAdvanceUnit(�i�R���j�b�g�N���X)
// ��@���@���F2022/12/4
#include "AdvanceUnit.h"

#include <functional>
#include "GameParameter.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../02_Library/Math.h"
#include "../../02_Library/Utility.h"


#include <iostream>

AdvanceUnit::AdvanceUnit(std::shared_ptr<Parameter> param)
: mRouteCount(0)
, mFirstPosX(0), mFirstPosZ(0)
, mMoveSpeed(0)
, mHitPoint(0)
, mAddCoin(0)
, mMesh(nullptr)
{
	mUnitInfo = tkl::LoadCsv(CSV_PATH);
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
	mSound = tkl::Sound::CreateSound(DISAPPER_SOUND);

	mIsRetNewRoute = false;
	mPrevRouteCount = 0;
}

AdvanceUnit::~AdvanceUnit()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F����������
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�i�R���j�b�g�N���X�̕`�揈��
//****************************************************************************
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
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));

	int level = mParam->GetAdvenceLevel();
	if(stoi(mUnitInfo[level][0]) <= mParam->GetTotalDefeat() && (level + 1) < mUnitInfo.size()){
		mParam->SetAdvanceLevel(level + 1);
		mParam->SetTotalDefeat(0);
	}
	mHitPoint = stoi(mUnitInfo[level][1]);
	mMoveSpeed = stoi(mUnitInfo[level][2]);
	mAddCoin = stoi(mUnitInfo[level][3]);
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
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

	// �ړ��ʌv�Z
	int column = (mIsRetNewRoute) ? mPrevRoute[mPrevRouteCount - 1].column : mRoute[mRouteCount].column;
	int row = (mIsRetNewRoute) ? mPrevRoute[mPrevRouteCount - 1].row : mRoute[mRouteCount].row;

	int dx = mRoute[mRouteCount - 1].column - column;
	int dz = mRoute[mRouteCount - 1].row - row;

	//******************************************************************
	// �T�������o�H��i�ޏ���
	int mapSize = mParam->GetMapSize();
	float targetPosX = mFirstPosX + mapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mFirstPosZ + mapSize * mRoute[mRouteCount - 1].row;

	pos.mX += mMoveSpeed * dx * mParam->GetDeltaTime();
	pos.mZ += mMoveSpeed * dz * mParam->GetDeltaTime();

	bool retX = (dx > 0) ? pos.mX > targetPosX : pos.mX < targetPosX;
	if(retX){ pos.mX = targetPosX; }

	bool retZ = (dz > 0) ? pos.mZ > targetPosZ : pos.mZ < targetPosZ;
	if(retZ){ pos.mZ = targetPosZ; }

	bool isIncrement = (dx == 0 || dz == 0) ? retX || retZ : retX && retZ;
	if(isIncrement && mRouteCount > 0){
		mRouteCount--;
		if(mIsRetNewRoute){ mIsRetNewRoute = false;}
	}
	//******************************************************************

	mMesh->SetPosition(pos);
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�i�R���j�b�g�N���X�̕`�揈��
//****************************************************************************
void AdvanceUnit::Draw()
{
//	PrintRoute();

	mMesh->Draw(mParam->GetCamera());
}

//****************************************************************************
// �֐����FIsAlive
// �T�@�v�F�������Ă��邩
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������Ă��邩�̊m�F
//****************************************************************************
bool AdvanceUnit::IsAlive()
{
	if(!mIsAlive && mHitPoint <= 0){
		mParam->SetTotalCost(mParam->GetTotalCost() + mAddCoin);
		mParam->SetTotalDefeat(mParam->GetTotalDefeat() + 1);
		mSound->Play();
	}
	return mIsAlive;
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
	if(mHitPoint <= 0){ mIsAlive = false; }
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
	if(IsPassing()){
		printf("�ʂ�߂��Ă��܂�\n"); 
		return;
	}
	printf("�ʂ�߂��Ă��܂���\n");

	// �i�s�σ��[�g�J�E���g�̍Čv�Z
	int prevSize = mRoute.size(), currentSize = newRoute.size();
	int diffSize = abs(prevSize - currentSize);
	int newRoutCount = mRouteCount + diffSize;

	// �V���[�g�ɖ߂邩�m�F
	if((mRoute[mRouteCount - 1].row != newRoute[newRoutCount - 1].row) ||
		(mRoute[mRouteCount - 1].column != newRoute[newRoutCount - 1].column))
	{
		printf("�V���[�g�ɖ߂�܂�\n");
		mPrevRoute = mRoute;
		mPrevRouteCount = mRouteCount;
		mIsRetNewRoute = true;
	}

	// ���[�g�X�V
	mRouteCount = newRoutCount;
	mRoute = newRoute;
}

// �ʉ߂��Ă��邩
bool AdvanceUnit::IsPassing()
{
	// �ړ������v�Z
	int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	tkl::Vector3 pos = mMesh->GetPosition();
	tkl::Vector3 clickPos = mParam->GetClickPos();

	bool retX = false, retZ = false;
	if(dx != 0){ retX = (dx > 0) ? pos.mX > clickPos.mX : pos.mX < clickPos.mX; }
	if(dz != 0){ retZ = (dz > 0) ? pos.mZ > clickPos.mZ : pos.mZ < clickPos.mZ; }

	return (dx == 0 || dz == 0) ? retX || retZ : retX && retZ;
}

// ���[�g�\��(�f�o�b�O�p)
void AdvanceUnit::PrintRoute()
{
	for (int i = 0; i < mRoute.size(); ++i) {
		std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(50);

        float posX = mFirstPosX + 50 * mRoute[i].column;
        float posZ = mFirstPosZ + 50 * mRoute[i].row;
        mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/debug/test.jpg"));
        mesh->SetPosition(tkl::Vector3(posX, 0.1f, posZ));
        mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
        mesh->Draw(mParam->GetCamera());
	}
}