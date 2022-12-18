//****************************************************************************
// �t�@�C�����FField(�t�B�[���h�N���X)
// ��@���@���F2022/12/11
#include "Field.h"

#include "GameObject/Cell.h"
#include "GameObject/ObjectManager.h"
#include "GameObject/GameParameter.h"

#include "../01_Engine/Camera/Camera.h"
#include "../01_Engine/System.h"
#include "../01_Engine/Intersect.h"

#include "../02_Library/Input.h"
#include "../02_Library/Utility.h"

Field::Field(std::shared_ptr<Parameter> param)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);

	// �t�B�[���h���ǂݍ���
	auto readField = tkl::LoadCsv("Resource/debug/test.csv");
	mParam->SetMapSize(MAP_SIZE);
	mParam->SetMapRow(readField.size());
	mParam->SetMapColumn(readField[0].size());

	// �t�B�[���h����
	std::vector<std::vector<tkl::CELL>> fields;
	for(int r = 0; r < readField.size(); ++r){
		std::vector<tkl::CELL> cells;
		for(int c = 0; c < readField[r].size(); ++c){
			tkl::CELL cell = {r, c, static_cast<tkl::STATUS>(stoi(readField[r][c]))};
			cells.emplace_back(cell);

			std::shared_ptr<Cell> object = ObjectManager::GetInstance()->Create<Cell>(param);
			object->SetCellInfo(cell);
			object->Initialize();
		}
		fields.emplace_back(cells);
	}
	mParam->SetFields(fields);
}

Field::~Field()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�t�B�[���h�N���X�̍X�V����
//****************************************************************************
void Field::Update()
{
	UpdateMousePos();

	// �Z���̏�Ԃ��X�V
	auto fields = mParam->GetFields();
	auto list = ObjectManager::GetInstance()->GetList<Cell>();
	for(auto it = list->begin(); it != list->end(); ++it){
		auto cell = std::dynamic_pointer_cast<Cell>(*it);
		tkl::CELL info = cell->GetCellInfo();

		cell->SetCellInfo(fields[info.row][info.column]);
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�t�B�[���h�N���X�̕`�揈��
//****************************************************************************
void Field::Draw()
{}

//****************************************************************************
// �֐����FUpdateMousePos(private)
// �T�@�v�F�`��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�E�X���W���X�V(2D��ʍ��W��3D���W�����߂Ă���)
//****************************************************************************
void Field::UpdateMousePos()
{
	// �E�B���h�E�T�C�Y���擾
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);

	// �}�E�X���W�����Ƀ��C���΂�
	int screenMouseX = 0, screenMouseY = 0;
	tkl::Input::GetMousePoint(&screenMouseX, &screenMouseY);

	std::shared_ptr<tkl::Camera> camera = mParam->GetCamera();
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(screenMouseX, screenMouseY,
		screenW, screenH, camera->GetView(), camera->GetProjection());

	// ���C�ƕ��ʂ̏Փ˔���
	tkl::Vector3 mousePos;
	tkl::IsIntersectLinePlane(camera->GetPosition(), camera->GetPosition() + ray * 1000.0f,
		{ 1, 0, 0 }, tkl::Vector3::UNITY, &mousePos);
	mParam->SetMousePos(mousePos);
}