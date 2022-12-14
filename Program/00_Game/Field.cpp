//****************************************************************************
// �t�@�C�����FField(�t�B�[���h�N���X)
// ��@���@���F2022/12/11
#include "Field.h"

#include "../00_Game/GameObject/GameParameter.h"
#include "../00_Game/NotifyService/Notifier.h"

#include "../01_Engine/Camera/Camera.h"
#include "../01_Engine/Mesh.h"
#include "../01_Engine/System.h"
#include "../01_Engine/Intersect.h"
#include "../01_Engine/ResourceManager.h"

#include "../02_Library/Input.h"
#include "../02_Library/Utility.h"
#include "../02_Library/Math.h"

const int MAP_SIZE = 50;

Field::Field(std::shared_ptr<GameParameter> param)
: mScreenW(0), mScreenH(0)
, mStartPosX(0), mStartPosZ(0)
, mCursor(nullptr)
, mGrid(nullptr)
{
	// �O���b�h����
	mGrid = tkl::Mesh::CreateGround(50, 5);

	// �E�B���h�E�T�C�Y���擾
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);

	// �J�[�\������
	mCursor = tkl::Mesh::CreatePlane(50);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test2.bmp"));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	// �t�B�[���h���ǂݍ���
	auto readField = tkl::LoadCsv("Resource/test.csv");
	for(int r = 0; r < readField.size(); ++r){
		std::vector<tkl::CELL> fields;
		for(int c = 0; c < readField[r].size(); ++c){
			fields.emplace_back(tkl::CELL(r, c, static_cast<tkl::STATUS>(std::stoi(readField[r][c]))));
		}
		mFields.emplace_back(fields);
	}

	int mapRow = readField.size();
	int mapColumn = readField[0].size();

	// �X�^�[�g�ʒu���v�Z
	mStartPosX = -MAP_SIZE * mapRow * 0.5f + (MAP_SIZE >> 1);
	mStartPosZ = -MAP_SIZE * mapColumn * 0.5f + (MAP_SIZE >> 1);

	param->SetMapSize(MAP_SIZE);
	param->SetMapRow(mapRow);
	param->SetMapColumn(mapColumn);
	param->SetFields(mFields);
}

Field::~Field()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�t�B�[���h�N���X�̍X�V����
//****************************************************************************
void Field::Update(std::shared_ptr<GameParameter>& param)
{
	std::shared_ptr<tkl::Camera> camera = param->GetCamera();

	// �}�E�X���W�����Ƀ��C���΂�
	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(mousePosX, mousePosY,
		mScreenW, mScreenH, camera->GetView(), camera->GetProjection());

	// ���C�ƕ��ʂ̓����蔻��
	tkl::Vector3 hit;
	if (tkl::IsIntersectLinePlane(camera->GetPosition(), camera->GetPosition() + ray * 1000.0f,
		{ 1, 0, 0 }, tkl::Vector3::UNITY, &hit))
	{
		PriSelectField(param, hit);
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�t�B�[���h�N���X�̕`�揈��
//****************************************************************************
void Field::Draw(std::shared_ptr<GameParameter>& param)
{
	// �O���b�h����
	mGrid->Draw(param->GetCamera());
}

//****************************************************************************
// �֐����FPriSelectField(private)
// �T�@�v�F�t�B�[���h�I��
// ���@���Farg1 �Q�[���p�����[�^
//       �Farg2 ���C�ƕ��ʂ̓��������ʒu
// �߂�l�F�Ȃ�
// �ځ@�ׁF�t�B�[���h�̂ǂ̈ʒu�ɖh�q���j�b�g��u�����I������
//****************************************************************************
void Field::PriSelectField(std::shared_ptr<GameParameter> param, const tkl::Vector3& pos)
{
	for (int r = 0; r < mFields.size(); ++r) {
		for (int c = 0; c < mFields[r].size(); ++c) {
			float posX = mStartPosX + MAP_SIZE * c;
			float posZ = mStartPosZ + MAP_SIZE * r;
			if (!tkl::IsIntersectPointRect(pos.mX, pos.mZ, posX, posZ, MAP_SIZE)) { continue; }

			// �ҏW��Ԃ̂ݏ�������
			if(mFields[r][c].status == tkl::STATUS::EDITABLE){

				mCursor->SetPosition(tkl::Vector3(posX, 0, posZ));
				mCursor->Draw(param->GetCamera());

				if(!tkl::Input::IsMouseDownTrigger(tkl::eMouse::MOUSE_LEFT)) { continue; }

				// �t�B�[���h��ԕω��ʒm
				param->SetClickPos(tkl::Vector3(posX, 0, posZ));
				Notifier::GetInstance()->FieldStateChange(r, c, param);
			}
		}
	}
}