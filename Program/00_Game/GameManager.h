//****************************************************************************
// �t�@�C�����FGameManager(�Q�[���Ǘ��҃N���X)
// ��@���@���F2022/10/6
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include <memory>

class SceneManager;
class GameManager
{
public:

	static GameManager* GetInstance();
	static void DestoryInstance();

	void Update(float deltaTime);

private:
	GameManager();
	~GameManager();
	GameManager(const GameManager&){}
	GameManager& operator=(const GameManager&){}

private:
	static GameManager* sMyInstance;
	std::shared_ptr<SceneManager> mSceneManager;
};

#endif