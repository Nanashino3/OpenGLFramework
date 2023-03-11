//****************************************************************************
// �t�@�C�����FPauseScene(�|�[�Y��ʃN���X)
// ��@���@���F2022/12/15
#ifndef _PAUSESCENE_H_
#define _PAUSESCENE_H_

#include "SceneBase.h"

namespace tkl{ class Sound; }

class PauseScene : public SceneBase
{
public:
	PauseScene();
	virtual ~PauseScene();

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	std::shared_ptr<tkl::Sound> mSndCancel;
};

#endif