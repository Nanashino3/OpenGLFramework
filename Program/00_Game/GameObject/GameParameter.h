//****************************************************************************
// ファイル名：GameParameter(ゲームパラメータクラス)
// 作　成　日：2022/12/8
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
	, mIsArrival(false)
	, mCamera(nullptr)
	, mClickPos(tkl::Vector3::ZERO)
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
	void SetIsArrival(bool value){ mIsArrival = value; }
	bool GetIsArrival() const { return mIsArrival; }
	void SetCamera(std::shared_ptr<tkl::Camera> camera) { mCamera = camera; }
	std::shared_ptr<tkl::Camera> GetCamera() { return mCamera; }
	void SetClickPos(const tkl::Vector3& pos){ mClickPos = pos; }
	const tkl::Vector3& GetClickPos() { return mClickPos; }
	void SetRoute(std::vector<tkl::CELL>& route) { mRoute = route; }
	std::vector<tkl::CELL>& GetRoute() { return mRoute; }
	void SetFields(std::vector<std::vector<tkl::CELL>>& fields){ mFields = fields; }
	std::vector<std::vector<tkl::CELL>>& GetFields() { return mFields; }

private:
	float mDeltaTime;
	int mMapSize;
	int mMapRow, mMapColumn;
	bool mIsArrival;
	std::shared_ptr<tkl::Camera> mCamera;

	tkl::Vector3 mClickPos;

	std::vector<tkl::CELL> mRoute;
	std::vector<std::vector<tkl::CELL>> mFields;
};

#endif