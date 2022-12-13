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
	AdvanceUnit(std::shared_ptr<GameParameter> param);
	virtual ~AdvanceUnit();

	virtual void Update(std::shared_ptr<GameParameter>& param) final;
	void ReceiveDamage(int damage);
	tkl::Vector3 GetUnitPosition() const;

private:
	void Move(std::shared_ptr<GameParameter> param);
	void Draw(std::shared_ptr<GameParameter> param);
	void SetNewRoute(std::vector<tkl::CELL>& newRoute);

private:
	int mRouteCount;
	float mFirstPosX, mFirstPosZ;
	float mMoveSpeed;
	int mHitPoint;

	std::shared_ptr<tkl::Mesh> mMesh;
	std::vector<tkl::CELL> mRoute;
};

#endif