//****************************************************************************
// �t�@�C�����FCell(�}�X�N���X)
// ��@���@���F2022/12/17
#include "Cell.h"

#include "../GameObject/GameParameter.h"
#include "../NotifyService/Notifier.h"

#include "../../01_Engine/Intersect.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

static constexpr int PLANE_SIZE = 50;
static constexpr int BLOCK_SIZE = 30;
static constexpr const char* TEXTURE_FIELD  = "Resource/texture/panel_soil.bmp";
static constexpr const char* TEXTURE_BLOCK  = "Resource/texture/panel_grass.bmp";
static constexpr const char* TEXTURE_START  = "Resource/texture/red.png";
static constexpr const char* TEXTURE_GAOL   = "Resource/texture/blue.png";
static constexpr const char* TEXTURE_CURSOR = "Resource/texture/frame_green.png";

Cell::Cell(std::shared_ptr<Parameter> param)
: mCursor(nullptr)
, mIsSelecting(false)
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
void Cell::Initialize(const tkl::CELL& cell)
{
	// ���W�v�Z
	int mapSize = mParam->GetMapSize();
	int mapRow = mParam->GetMapRow();
	int mapColumn = mParam->GetMapColumn();
	
	float initPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	float initPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	float posX = initPosX + mapSize * cell.column;
	float posZ = initPosZ + mapSize * cell.row;

	//*****************************************************************************************
	// TODO�F�}�X�ɉ��𐶐����邩����ԂŌ��߂�
	
	// �t���A����
	std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(PLANE_SIZE);
	mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FIELD));
	mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
	mesh->SetPosition(tkl::Vector3(posX, 0, posZ));
	mMeshList.emplace_back(mesh);

	// �G�o���ʒu�ƃS�[���ʒu�̐���
	if(cell.status == tkl::STATUS::START || cell.status == tkl::STATUS::GOAL){
		mesh = tkl::Mesh::CreatePlane(PLANE_SIZE);
		mesh->SetIsBlend(true);
		mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
		mesh->SetPosition(tkl::Vector3(posX, 0.1f, posZ));

		// �e�N�X�`���̐ݒ�
		std::string file = "";
		if(cell.status == tkl::STATUS::START){
			file = TEXTURE_START;
		}else if(cell.status == tkl::STATUS::GOAL){
			file = TEXTURE_GAOL;
		}
		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(file.c_str()));

		mMeshList.emplace_back(mesh);
	}

	// ��Q������
	if(cell.status == tkl::STATUS::OBSTACLE){
		mesh = tkl::Mesh::CreateBox(BLOCK_SIZE);
		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_BLOCK));
		mesh->SetPosition(tkl::Vector3(posX, BLOCK_SIZE >> 1, posZ));
		mMeshList.emplace_back(mesh);
	}
	//*****************************************************************************************

	// �J�[�\������
	mCursor = tkl::Mesh::CreatePlane(50);
	mCursor->SetIsBlend(true);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_CURSOR));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	mCell = cell;
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
	mIsSelecting = false;
	tkl::Vector3 pos = mMeshList.at(0)->GetPosition();
	if(tkl::IsIntersectPointRect(mousePos.mX, mousePos.mZ, pos.mX, pos.mZ, mParam->GetMapSize())){
		if(mCell.status != tkl::STATUS::EDITABLE){ return; }

		mIsSelecting = true;
		mCursor->SetPosition(tkl::Vector3(pos.mX, 0.5f, pos.mZ));

		if(tkl::Input::IsMouseDownTrigger(tkl::eMouse::MOUSE_LEFT)){

			// �t�B�[���h��ԕω��ʒm
			mParam->SetClickPos(tkl::Vector3(pos.mX, 0, pos.mZ));
			Notifier::GetInstance()->FieldStateChange(mCell.row, mCell.column, mParam);
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
	for(auto mesh : mMeshList){
		mesh->Draw(mParam->GetCamera());
	}
	
	if(mIsSelecting){ mCursor->Draw(mParam->GetCamera()); }
}