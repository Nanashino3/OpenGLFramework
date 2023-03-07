#ifndef _EFFECTBOMB_H_
#define _EFFECTBOMB_H_

#include <memory>
#include "EffectBase.h"

namespace tkl
{
class Sprite;
class Camera;
class Vector3;
}

class Parameter;
class EffectBomb : public EffectBase
{
public:
	EffectBomb(std::shared_ptr<Parameter> param);
	virtual ~EffectBomb();
	
	void Initialize(const tkl::Vector3& drawPosition);

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	std::shared_ptr<Parameter> mParam;
	std::shared_ptr<tkl::Sprite> mSprite;
	std::shared_ptr<tkl::Camera> m2DCam;
};

#endif