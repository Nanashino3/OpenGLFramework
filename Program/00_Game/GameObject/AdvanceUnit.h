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
namespace tkl
{
class Model;
class Sound;
}

class AdvanceUnit : public GameObject
{
public:
	AdvanceUnit(std::shared_ptr<Parameter> param);
	virtual ~AdvanceUnit();

	void Initialize();
	void ReceiveDamage(int damage);

	void SetNewRoute(const std::vector<tkl::CELL>& newRoute);
	const tkl::Vector3& GetPosition() const;
	float GetHitPoint() const{ return mHitPoint; } 

	virtual void Update();
	virtual void Draw();
	virtual bool IsAlive();

private:
	bool IsPassing();
	void PrintRoute();

private:
	int mRouteCount;					// ルート配列のカウンター用
	int mAddCoin;
	int mPrevDx, mPrevDz;				// 前の進行方向(X、Z)
	int mPrevRouteCount;				// 前のルートカウンター

	float mHitPoint;
	float mMapInitPosX, mMapInitPosZ;	// マップの初期座標(X、Z)
	float mMoveSpeed;
	float mAngle;
	
	bool mIsRetNewRoute;				// 新ルートに戻るか

	std::shared_ptr<tkl::Model> mModel;
	std::shared_ptr<tkl::Sound> mSound;
	std::shared_ptr<GameParameter> mParam;

	std::vector<tkl::CELL> mRoute;
	std::vector<tkl::CELL> mPrevRoute;
	std::vector<std::vector<std::string>> mUnitInfo;
};

#endif