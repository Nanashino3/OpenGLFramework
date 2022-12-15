//****************************************************************************
// ファイル名：AdvanceUnit(進軍ユニットクラス)
// 作　成　日：2022/12/4
#ifndef _ADVANCEUNIT_H_
#define _ADVANCEUNIT_H_

#include <memory>
#include <vector>
#include "GameObject.h"
#include "../../01_Engine/Algorithm.h"

class GameParameter;
namespace tkl{ class Mesh; }

class AdvanceUnit : public GameObject
{
public:
	AdvanceUnit(std::shared_ptr<Parameter> param);
	virtual ~AdvanceUnit();

	virtual void Initialize() final;
	virtual void Update() final;
	virtual void Draw() final;

	void ReceiveDamage(int damage);

	void SetNewRoute(const std::vector<tkl::CELL>& newRoute);
	tkl::Vector3 GetUnitPosition() const;

private:
	int mRouteCount;
	float mFirstPosX, mFirstPosZ;
	float mMoveSpeed;
	int mHitPoint;

	std::shared_ptr<tkl::Mesh> mMesh;
	std::shared_ptr<GameParameter> mParam;
	std::vector<tkl::CELL> mRoute;
};

#endif