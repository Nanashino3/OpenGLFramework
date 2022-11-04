#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_
#include "BaseScene.h"

class PlayScene : public BaseScene, public std::enable_shared_from_this<PlayScene>
{
public:
	PlayScene();
	virtual ~PlayScene();

	virtual std::shared_ptr<BaseScene> Update() final;
};
#endif