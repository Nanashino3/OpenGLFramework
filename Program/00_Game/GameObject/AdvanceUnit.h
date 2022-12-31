//****************************************************************************
// ファイル名：AdvanceUnit(進軍ユニットクラス)
// 作　成　日：2022/12/4
#ifndef _ADVANCEUNIT_H_
#define _ADVANCEUNIT_H_

#include <memory>
#include <vector>
#include <string>
#include "GameObject.h"
#include "../../01_Engine/Algorithm.h"

class GameParameter;
namespace tkl{
class Model;
class Sound;
}

class AdvanceUnit : public GameObject
{
public:
	AdvanceUnit(std::shared_ptr<Parameter> param);
	virtual ~AdvanceUnit();

	virtual void Initialize() final;
	virtual void Update() final;
	virtual void Draw() final;
	virtual bool IsAlive() final;

	void ReceiveDamage(int damage);

	void SetNewRoute(const std::vector<tkl::CELL>& newRoute);
	tkl::Vector3 GetUnitPosition() const;

private:
	bool IsPassing();
	void PrintRoute();

private:
	int mRouteCount;
	float mFirstPosX, mFirstPosZ;
	float mMoveSpeed;
	int mHitPoint;
	int mAddCoin;
	int mPrevDx, mPrevDz;
	float mAngle;

	std::shared_ptr<tkl::Model> mModel;
	std::shared_ptr<tkl::Sound> mSound;
	std::shared_ptr<GameParameter> mParam;
	std::vector<tkl::CELL> mRoute;
	std::vector<std::vector<std::string>> mUnitInfo;

	int mPrevRouteCount;
	bool mIsRetNewRoute;
	std::vector<tkl::CELL> mPrevRoute;
};

#endif