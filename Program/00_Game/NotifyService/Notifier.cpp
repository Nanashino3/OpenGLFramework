//****************************************************************************
// �t�@�C�����FNotifier(�ʒm�҃N���X)
// ��@���@���F2022/12/11
#include "Notifier.h"

#include "Observer.h"

Notifier* Notifier::sMyInstance = nullptr;
Notifier::Notifier()
{}

Notifier::~Notifier()
{}

Notifier* Notifier::GetInstance()
{
	if(!sMyInstance) sMyInstance = new Notifier;
	return sMyInstance;
}

void Notifier::DestroyInstance()
{
	delete sMyInstance;
}

//****************************************************************************
// �֐����FFieldStateChange
// �T�@�v�F�t�B�[���h��ԕω�
// ���@���Farg1 �s
//       �Farg2 ��
//       �Farg3 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�t�B�[���h�̏�Ԃɕω������������Ƃ�ʒm����
//****************************************************************************
void Notifier::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	for(int i = 0; i < mObservers.size(); ++i){
		mObservers[i]->FieldStateChange(row, column, param);
	}
}