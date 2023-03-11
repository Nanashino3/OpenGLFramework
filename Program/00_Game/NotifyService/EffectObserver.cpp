#include "EffectObserver.h"

#include "../Scene/GameScene.h"
#include "../GameObject/GameParameter.h"
#include "../Graphics/Effect/EffectBomb.h"

EffectObserver::EffectObserver(std::shared_ptr<GameScene> gameScene)
: mGameScene(gameScene)
{}
	
EffectObserver::~EffectObserver()
{}

void EffectObserver::DefeatAdvanceUnit(std::shared_ptr<GameParameter> param, const tkl::Vector3& position)
{
	std::shared_ptr<EffectBomb> newEffect = std::make_shared<EffectBomb>(param);
	newEffect->Initialize(position);

	mGameScene.lock()->AddEffect(newEffect);
}