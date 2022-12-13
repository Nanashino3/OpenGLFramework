//****************************************************************************
// �t�@�C�����FObjectManager(�I�u�W�F�N�g�Ǘ���)
// ��@���@���F2022/12/8
#include "ObjectManager.h"
#include "GameObject.h"
#include "GameParameter.h"

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
	delete sMyInstance;
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����(�I�u�W�F�N�g)
// ���@���Farg1 �Q�[���p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�}�b�v�ɓo�^�ς̃I�u�W�F�N�g���X�g�ɑ΂��čX�V������������
//****************************************************************************
void ObjectManager::Update(std::shared_ptr<GameParameter>& param)
{
	for(auto map : mListMap){
		auto list = &mListMap[map.first];
		for(auto it = list->begin(); it != list->end();){
			(*it)->Update(param);
			if (!(*it)->IsAlive()){ it = list->erase(it); continue; }
			++it;
		}
	}
}