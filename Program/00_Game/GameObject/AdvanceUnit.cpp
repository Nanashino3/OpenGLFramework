//****************************************************************************
// �t�@�C�����FAdvanceUnit(�i�R���j�b�g�N���X)
// ��@���@���F2022/12/4
#include "AdvanceUnit.h"

#include <iostream>
#include "GameParameter.h"

#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Utility.h"

static constexpr const char* CSV_PATH = "Resource/AdvanceInfo.csv";
static constexpr const char* OBJECT_FILE = "Resource/model/UFO/TriangleUFO.obj";
static constexpr const char* DISAPPER_SOUND = "Resource/sound/disapper.wav";

AdvanceUnit::AdvanceUnit(std::shared_ptr<Parameter> param)
: mRouteCount(0)
, mMapInitPosX(0), mMapInitPosZ(0)
, mMoveSpeed(0)
, mHitPoint(0)
, mAddCoin(0)
, mPrevDx(0), mPrevDz(0)
, mAngle(0)
, mModel(nullptr)
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
	std::vector<std::vector<tkl::CELL>> field = mParam->GetFields();

	// �o�H����(����)
	tkl::Algorithm::RouteSearch(mapRow, mapColumn, field, mRoute);
	
	// �����ړ������v�Z
	mRouteCount = mRoute.size() - 1;
	mPrevDx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	mPrevDz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	if(mPrevDx != 0){ mAngle = (mPrevDx > 0) ?  90 : 270; }
	if(mPrevDz != 0){ mAngle = (mPrevDz > 0) ? 180 : 360; }
	tkl::Quaternion rot;
	rot *= tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(mAngle));

	// �������W�v�Z
	mMapInitPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	mMapInitPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	float posX = mMapInitPosX + mParam->GetMapSize() * mRoute[mRouteCount].column;
	float posZ = mMapInitPosZ + mParam->GetMapSize() * mRoute[mRouteCount].row;

	// ���f���̐����Ɛݒ�
	mModel = tkl::Model::CreateModelFromObjFile(OBJECT_FILE);
	mModel->SetPosition(tkl::Vector3(posX, 10, posZ));
	mModel->SetScale(tkl::Vector3(3.5f, 3.5f, 3.5f));
	mModel->SetRotation(rot);

	// �i�R���j�b�g�̃��x���ݒ�
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
	if(mRouteCount == 0 && mRoute[mRouteCount].status == tkl::STATUS::GOAL){
		mIsAlive = false;
		mParam->SetIsArrival(true);
		return;
	}
	tkl::Vector3 pos = mModel->GetPosition();
	tkl::Quaternion rot = mModel->GetRotation();

	//******************************************************************
	// �ړ��ʌv�Z
	int column = (mIsRetNewRoute) ? mPrevRoute[mPrevRouteCount - 1].column : mRoute[mRouteCount].column;
	int row = (mIsRetNewRoute) ? mPrevRoute[mPrevRouteCount - 1].row : mRoute[mRouteCount].row;

	int dx = mRoute[mRouteCount - 1].column - column;
	int dz = mRoute[mRouteCount - 1].row - row;
	//******************************************************************

	//******************************************************************
	// �����]���v�Z
	float angles[] = { 90, 180, 270, 360 };
	enum { RIGHT, BOTTOM, LEFT, TOP };

	float diffAngle = 0;
	if(dx != 0 && mPrevDx != dx){
		int dir = (dx > 0) ? RIGHT : LEFT;
		diffAngle = angles[dir] - mAngle;
	}

	if(dz != 0 && mPrevDz != dz){
		int dir = (dz > 0) ? BOTTOM : TOP;
		diffAngle = angles[dir] - mAngle;
	}
	rot *= tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(diffAngle));
	mAngle += diffAngle;
	//******************************************************************

	//******************************************************************
	// �T�������o�H��i�ޏ���
	int mapSize = mParam->GetMapSize();
	float targetPosX = mMapInitPosX + mapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mMapInitPosZ + mapSize * mRoute[mRouteCount - 1].row;

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

	mPrevDx = dx, mPrevDz = dz;

	mModel->SetPosition(pos);
	mModel->SetRotation(rot);
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
	mModel->Draw(mParam->GetCamera());
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
// �֐����FGetPosition
// �T�@�v�F���W�擾
// ���@���F�Ȃ�
// �߂�l�F���f���̍��W
// �ځ@�ׁF�i�R���j�b�g���g�̈ʒu��Ԃ�
//****************************************************************************
const tkl::Vector3& AdvanceUnit::GetPosition() const
{
	return mModel->GetPosition();
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
//		printf("�ʂ�߂��Ă��܂�\n"); 
		return;
	}
//	printf("�ʂ�߂��Ă��܂���\n");

	// �i�s�σ��[�g�J�E���g�̍Čv�Z
	int prevSize = mRoute.size(), currentSize = newRoute.size();
	int diffSize = abs(prevSize - currentSize);
	int newRoutCount = mRouteCount + diffSize;

	// �V���[�g�ɖ߂邩�m�F
	if((mRoute[mRouteCount - 1].row != newRoute[newRoutCount - 1].row) ||
		(mRoute[mRouteCount - 1].column != newRoute[newRoutCount - 1].column))
	{
//		printf("�V���[�g�ɖ߂�܂�\n");
		mPrevRoute = mRoute;
		mPrevRouteCount = mRouteCount;
		mIsRetNewRoute = true;
	}

	// ���[�g�X�V
	mRouteCount = newRoutCount;
	mRoute = newRoute;
}

//****************************************************************************
// �֐����FIsPassing(private)
// �T�@�v�F�ʉ߂��Ă��邩
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�V���[�g��ݒ肷��ۂɎw�肵���Z����ʉ߂��Ă��邩�ǂ�����
//       �F�V���[�g�ɖ߂邩�ǂ����𔻒肷��
//****************************************************************************
bool AdvanceUnit::IsPassing()
{
	// �����ʒu����s������߂�
	tkl::Vector3 clickPos = mParam->GetClickPos();
	int clickColumn = abs((mMapInitPosX - clickPos.mX) / mParam->GetMapSize());
	int clickRow    = abs((mMapInitPosZ - clickPos.mZ) / mParam->GetMapSize());

	int nowColumn = mRoute[mRouteCount].column;
	int nowRow = mRoute[mRouteCount].row;

	// �i�R���j�b�g�̈ʒu�Ɠ����ʒu�ɒu���ꂽ�ꍇ�̂ݒʉߔ��肷��
	if(clickColumn == nowColumn && clickRow == nowRow){
		// �ړ������v�Z
		int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
		int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

		tkl::Vector3 pos = mModel->GetPosition();

		bool retX = false, retZ = false;
		if (dx != 0) { retX = (dx > 0) ? pos.mX > clickPos.mX : pos.mX < clickPos.mX; }
		if (dz != 0) { retZ = (dz > 0) ? pos.mZ > clickPos.mZ : pos.mZ < clickPos.mZ; }

		return (dx == 0 || dz == 0) ? retX || retZ : retX && retZ;
	}

	return false;
}

//****************************************************************************
// �֐����FPrintRoute(private)
// �T�@�v�F���[�g�\��(�f�o�b�O�p)
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF���ݐi�s���̃��[�g��`�悷��
//****************************************************************************
void AdvanceUnit::PrintRoute()
{
	for (int i = 0; i < mRoute.size(); ++i) {
		std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(mParam->GetMapSize());

        float posX = mMapInitPosX + mParam->GetMapSize() * mRoute[i].column;
        float posZ = mMapInitPosZ + mParam->GetMapSize() * mRoute[i].row;
        mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/debug/route.bmp"));
        mesh->SetPosition(tkl::Vector3(posX, 0.1f, posZ));
        mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
        mesh->Draw(mParam->GetCamera());
	}
}