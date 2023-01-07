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

	void Initialize();

	virtual void Update();
	virtual void Draw();
	virtual bool IsAlive();

	void ReceiveDamage(int damage);

	void SetNewRoute(const std::vector<tkl::CELL>& newRoute);
	const tkl::Vector3& GetPosition() const;

private:
	bool IsPassing();
	void PrintRoute();

private:
	int mRouteCount;
	float mMapInitPosX, mMapInitPosZ;
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