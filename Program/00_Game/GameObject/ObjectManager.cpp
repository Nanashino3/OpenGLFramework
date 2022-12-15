//****************************************************************************
// �t�@�C�����FObjectManager(�I�u�W�F�N�g�Ǘ���)
// ��@���@���F2022/12/8
#include "ObjectManager.h"
#include "../../02_Library/Utility.h"

ObjectManager* ObjectManager::sMyInstance = nullptr;
ObjectManager::ObjectManager()
{}

ObjectManager::~ObjectManager()
{}

ObjectManager* ObjectManager::GetInstance()
{
	if(!sMyInstance) sMyInstance = new ObjectManager;
	return sMyInstance;
}
void ObjectManager::DestroyInstance()
{
	TKL_SAFE_DELETE(sMyInstance) ;
}

//****************************************************************************
// �֐����FCollision
// �T�@�v�F�Փ˔���(�I�u�W�F�N�g)
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�b�v�ɓo�^�ς̃I�u�W�F�N�g���X�g�ɑ΂��ďՓ˔�����s��
//****************************************************************************
void ObjectManager::Collision()
{
	for (auto map : mListMap) {
		auto list = &mListMap[map.first];
		for (auto it = list->begin(); it != list->end(); ++it) {
			(*it)->Collision();
		}
	}
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����(�I�u�W�F�N�g)
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�b�v�ɓo�^�ς̃I�u�W�F�N�g���X�g�ɑ΂��čX�V�������s��
//****************************************************************************
void ObjectManager::Update()
{
	for(auto map : mListMap){
		auto list = &mListMap[map.first];
		for(auto it = list->begin(); it != list->end();){
			(*it)->Update();
			if (!(*it)->IsAlive()){ it = list->erase(it); continue; }
			++it;
		}
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��(�I�u�W�F�N�g)
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�b�v�ɓo�^�ς̃I�u�W�F�N�g���X�g�ɑ΂��ĕ`�揈�����s��
//****************************************************************************
void ObjectManager::Draw()
{
	for (auto map : mListMap) {
		auto list = &mListMap[map.first];
		for (auto it = list->begin(); it != list->end(); ++it) {
			(*it)->Draw();
		}
	}
}