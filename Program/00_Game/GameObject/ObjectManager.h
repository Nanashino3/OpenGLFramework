//****************************************************************************
// �t�@�C�����FObjectManager(�I�u�W�F�N�g�Ǘ���)
// ��@���@���F2022/12/8
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <list>
#include <memory>
#include <unordered_map>
#include "GameObject.h"

class ObjectManager
{
public:
	static ObjectManager* GetInstance();
	static void DestroyInstance();

	//****************************************************************************
	// �֐����FCreate
	// �T�@�v�F�쐬(�V�K�I�u�W�F�N�g)
	// ���@���Farg1 �Q�[���p�����[�^
	// �߂�l�F�I�u�W�F�N�g�̃|�C���^
	// �ځ@�ׁF�V�K�I�u�W�F�N�g���쐬����B
	//       �@���쐬����I�u�W�F�N�g�̃��X�g���Ȃ���Έꏏ�ɍ쐬
	//****************************************************************************
	template <class T>
	std::shared_ptr<T> Create(std::shared_ptr<Parameter> param = nullptr)
	{
		std::shared_ptr<T> newObject = std::make_shared<T>(param);

		// ���X�g�ɃI�u�W�F�N�g���l�߂�
		auto list = mListMap[typeid(T).name()];
		list.emplace_back(newObject);
		mListMap[typeid(T).name()] = list;

		return newObject;
	}
	
	//****************************************************************************
	// �֐����FGetList
	// �T�@�v�F���X�g�擾
	// ���@���F�Ȃ�
	// �߂�l�F�w�肵���I�u�W�F�N�g�̃��X�g
	// �ځ@�ׁF�w�肵���I�u�W�F�N�g�̃��X�g��Ԃ�
	//****************************************************************************
	template <class T>
	const std::list<std::shared_ptr<GameObject>>* GetList()
	{
		return &mListMap[typeid(T).name()];
	}
	void Collision();
	void Update();
	void Draw();

private:
	ObjectManager();
	~ObjectManager();
	ObjectManager(const ObjectManager&){}
	ObjectManager& operator=(const ObjectManager&){}

private:
	static ObjectManager* sMyInstance;
	std::unordered_map<const char*, std::list<std::shared_ptr<GameObject>>> mListMap;
};

#endif