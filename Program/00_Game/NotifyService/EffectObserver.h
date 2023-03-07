#ifndef _EFFECTOBSERVER_H_
#define _EFFECTOBSERVER_H_

#include "Observer.h"

class GameScene;
class EffectObserver : public Observer
{
public:
	EffectObserver(std::shared_ptr<GameScene> gameScene);
	virtual ~EffectObserver();

	virtual void DefeatAdvanceUnit(std::shared_ptr<GameParameter> param, const tkl::Vector3& position);

private:
	std::shared_ptr<GameScene> mGameScene;
};

#endif