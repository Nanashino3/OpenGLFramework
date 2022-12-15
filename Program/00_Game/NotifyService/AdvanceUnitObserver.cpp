//****************************************************************************
// �t�@�C�����FAdvanceUnitObserver(�i�R���j�b�g�I�u�U�[�o�[)
// ��@���@���F2022/12/11
#include "AdvanceUnitObserver.h"

#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/ObjectManager.h"
#include "../GameObject/GameParameter.h"

AdvanceUnitObserver::AdvanceUnitObserver()
{}

AdvanceUnitObserver::~AdvanceUnitObserver()
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
void AdvanceUnitObserver::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	int mapRow = param->GetMapRow();
	int mapColumn = param->GetMapColumn();
	auto fields = param->GetFields();

	// �ҏW�s��Ԃɂ��Ă���
	fields[row][column].status = tkl::STATUS::UNEDITABLE;

	// �o�H�ĒT��
	std::vector<tkl::CELL> newRoute;
	if(tkl::Algorithm::RouteSearch(mapRow, mapColumn, fields, newRoute)) {
		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		for(auto it = list->begin(); it != list->end(); ++it){
			std::shared_ptr<AdvanceUnit> unit = std::dynamic_pointer_cast<AdvanceUnit>(*it);
			unit->SetNewRoute(newRoute);
		}
	}else{
		fields[row][column].status = tkl::STATUS::EDITABLE;
	}
	param->SetFields(fields);
}