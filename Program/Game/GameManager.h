#pragma once
#include <memory>
#include <vector>

class Renderer;
class Camera;
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
	static GameManager* sInstance;
	Renderer* mRenderer;
	Camera* mCamera;
};