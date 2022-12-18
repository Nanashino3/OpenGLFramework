//****************************************************************************
// �t�@�C�����FCell(�}�X�N���X)
// ��@���@���F2022/12/17
#include "Cell.h"

#include "../../00_Game/GameObject/GameParameter.h"
#include "../../00_Game/NotifyService/Notifier.h"

#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Intersect.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

Cell::Cell(std::shared_ptr<Parameter> param)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
}

Cell::~Cell()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F����������
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�X�N���X�̏���������
//****************************************************************************
void Cell::Initialize()
{
	// TODO�F�}�X�ɉ��𐶐����邩����ԂŌ��߂�
	mMesh = tkl::Mesh::CreatePlane(50);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FIELD));
	mMesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	// ���W�v�Z
	int mapSize = mParam->GetMapSize();
	int mapRow = mParam->GetMapRow();
	int mapColumn = mParam->GetMapColumn();
	
	float initPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	float initPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	float posX = initPosX + mapSize * mCellInfo.column;
	float posZ = initPosZ + mapSize * mCellInfo.row;

	mMesh->SetPosition(tkl::Vector3(posX, 0, posZ));

	// �J�[�\������
	mCursor = tkl::Mesh::CreatePlane(50);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_CURSOR));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
}

//****************************************************************************
// �֐����FCollision
// �T�@�v�F�Փˏ���
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�X�N���X�̏Փˏ���
//****************************************************************************
void Cell::Collision()
{
	tkl::Vector3 mousePos = mParam->GetMousePos();

	// �������I������Ă��邩�m�F
	tkl::Vector3 pos = mMesh->GetPosition();
	if(tkl::IsIntersectPointRect(mousePos.mX, mousePos.mZ, pos.mX, pos.mZ, mParam->GetMapSize())){
		if(mCellInfo.status != tkl::STATUS::EDITABLE){ return; }

		mCursor->SetPosition(tkl::Vector3(pos.mX, 0, pos.mZ));
		mCursor->Draw(mParam->GetCamera());

		if(tkl::Input::IsMouseDownTrigger(tkl::eMouse::MOUSE_LEFT)){

			// �t�B�[���h��ԕω��ʒm
			mParam->SetClickPos(tkl::Vector3(pos.mX, 0, pos.mZ));
			Notifier::GetInstance()->FieldStateChange(mCellInfo.row, mCellInfo.column, mParam);
		}
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�X�N���X�̕`�揈��
//****************************************************************************
void Cell::Draw()
{
	mMesh->Draw(mParam->GetCamera());
}