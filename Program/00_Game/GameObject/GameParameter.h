#ifndef _GAMEPARAMETER_H_
#define _GAMEPARAMETER_H_

#include <memory>
#include <vector>
#include "../../01_Engine/Algorithm.h"
#include "../../02_Library/Vector.h"

namespace tkl {
class Camera;
}
class GameParameter
{
public:
	GameParameter()
	: mDeltaTime(0)
	, mMapSize(0)
	, mMapRow(0), mMapColumn(0)
	, mCamera(nullptr)
	{}
	~GameParameter(){}

	void SetDeltaTime(float value) { mDeltaTime = value; }
	float GetDeltaTime() const { return mDeltaTime; }
	void SetMapSize(int value){ mMapSize = value; }
	int GetMapSize() const { return mMapSize; }
	void SetMapRow(int value){ mMapRow = value; }
	int GetMapRow() const { return mMapRow; }
	void SetMapColumn(int value){ mMapColumn = value; }
	int GetMapColumn() const { return mMapColumn; }
	void SetRoute(std::vector<tkl::CELL> route){ mRoute = route; }
	std::vector<tkl::CELL>& GetRoute(){ return mRoute; }
	void SetCamera(std::shared_ptr<tkl::Camera> camera) { mCamera = camera; }
	std::shared_ptr<tkl::Camera> GetCamera() { return mCamera; }
	void SetClickPos(const tkl::Vector3& pos){ mClickPos = pos; }
	const tkl::Vector3& GetClickPos() { return mClickPos; }
	void SetLauncherPos(const tkl::Vector3& pos) { mLauncherPos = pos; }
	const tkl::Vector3& GetLauncherPos() { return mLauncherPos; }
	void SetTargetPos(const tkl::Vector3& pos) { mTargetPos = pos; }
	const tkl::Vector3& GetTargetPos() { return mTargetPos; }

private:
	float mDeltaTime;
	int mMapSize;
	int mMapRow, mMapColumn;
	std::vector<tkl::CELL> mRoute;
	std::shared_ptr<tkl::Camera> mCamera;

	tkl::Vector3 mClickPos;		// クリック座標
	tkl::Vector3 mLauncherPos;	// 発射元座標
	tkl::Vector3 mTargetPos;	// 目標座標
};

#endif