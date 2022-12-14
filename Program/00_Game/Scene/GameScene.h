#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"
class GameScene : public SceneBase
{
public:
	GameScene(std::shared_ptr<SceneManager> manager);
	virtual ~GameScene();

	virtual void Initialize() final;
	virtual void Update(float deltaTime) final;
	virtual void Draw() final;
};

#endif