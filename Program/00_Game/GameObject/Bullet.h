#ifndef _BULLET_H_
#define _BULLET_H_

#include <memory>
#include "GameObject.h"
#include "../../02_Library/Vector.h"

class GameParameter;
namespace tkl{ class Mesh; }

class Bullet : public GameObject
{
public:
	Bullet(std::shared_ptr<Parameter> param);
	virtual ~Bullet();

	void Initialize(const tkl::Vector3& srcPos, const tkl::Vector3& target);

	virtual void Collision();
	virtual void Update();
	virtual void Draw();

private:
	float mRadian;
	tkl::Vector3 mLauncherPos;
	std::shared_ptr<tkl::Mesh> mMesh;
	std::shared_ptr<GameParameter> mParam;
};

#endif