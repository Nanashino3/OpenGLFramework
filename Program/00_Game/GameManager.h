//****************************************************************************
// ファイル名：GameManager(ゲーム管理者クラス)
// 作　成　日：2022/10/6
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include <memory>

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
};

#endif