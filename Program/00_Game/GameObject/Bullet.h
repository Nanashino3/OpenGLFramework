#ifndef _BULLET_H_
#define _BULLET_H_

#include <memory>
#include "GameObject.h"
#include "../../02_Library/Vector.h"

class GameParameter;
namespace tkl{ class Mesh; }

class Bullet : public GameObject
{
	const int BULLET_SIZE = 5;
	const float DESTROY_POS = 70.0f;
	const float MOVE_SPEED = 50.0f;
	const int DAMAGE = 5;

public:
	Bullet(std::shared_ptr<Parameter> param);
	virtual ~Bullet();

	virtual void Initialize() final;
	virtual void Collision() final;
	virtual void Update() final;
	virtual void Draw() final;
	void SetLauncherPos(const tkl::Vector3& pos){ mLauncherPos = pos; }
	void SetTargetPos(const tkl::Vector3& pos){ mTargetPos = pos; }

private:
	float mRadian;
	tkl::Vector3 mTargetPos;
	tkl::Vector3 mLauncherPos;
	std::shared_ptr<tkl::Mesh> mMesh;
	std::shared_ptr<GameParameter> mParam;
};

#endif