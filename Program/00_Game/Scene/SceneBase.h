//****************************************************************************
// �t�@�C�����FSceneBase(����ʃN���X)
// ��@���@���F2022/12/15
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include <memory>

class SceneManager;

class SceneBase
{
public:
	SceneBase(){}
	virtual ~SceneBase(){}
	
	virtual void Initialize(){}
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(){}
};

#endif