//****************************************************************************
// �t�@�C�����FDefenseUnitObserver(�h�q���j�b�g�I�u�U�[�o�[)
// ��@���@���F2022/12/11
#include "DefenseUnitObserver.h"

#include "../GameObject/DefenseUnit.h"
#include "../GameObject/ObjectManager.h"
#include "../GameObject/GameParameter.h"

static constexpr int CONSUME_COST = 75;

DefenseUnitObserver::DefenseUnitObserver()
{}

DefenseUnitObserver::~DefenseUnitObserver()
{}

//****************************************************************************
// �֐����FFieldStateChange
// �T�@�v�F�t�B�[���h��ԕω�
// ���@���Farg1 �t�B�[���h�̍s
//       �Farg2 �t�B�[���h�̗�
//       �Farg3 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�t�B�[���h�̏�Ԃ��ω��������Ƃ�ʒm����
//****************************************************************************
void DefenseUnitObserver::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	std::vector<std::vector<tkl::CELL>> fields = param->GetFields();

	// �h�q���j�b�g����
	if((fields[row][column].status == tkl::STATUS::OBSTACLE) &&
	   (param->GetTotalCost() >= CONSUME_COST)) {
		fields[row][column].status = tkl::STATUS::UNIT;
		std::shared_ptr<DefenseUnit> newObject = ObjectManager::GetInstance()->Create<DefenseUnit>(param);
		newObject->Initialize();
	}else{
		fields[row][column].status = tkl::STATUS::EDITABLE;
	}
	param->SetFields(fields);
}