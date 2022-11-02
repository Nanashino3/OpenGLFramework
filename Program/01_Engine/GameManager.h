#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include <memory>
#include <vector>

namespace tkl
{
class FixedCamera;
class PostureControlCamera;
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
	std::shared_ptr<FixedCamera> m2DCamera;
	std::shared_ptr<PostureControlCamera> m3DCamera;
};

} // namespace tkl

#endif