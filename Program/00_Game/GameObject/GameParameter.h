//****************************************************************************
// ファイル名：GameParameter(ゲームパラメータクラス)
// 作　成　日：2022/12/8
#ifndef _GAMEPARAMETER_H_
#define _GAMEPARAMETER_H_

#include <vector>
#include "Parameter.h"
#include "../../01_Engine/Algorithm.h"

class GameParameter : public Parameter
{
	const int INIT_TOTAL_COST = 125;
	const int INIT_LEVEL = 1;
public:
	GameParameter()
	: mMapSize(0)
	, mMapRow(0), mMapColumn(0)
	, mIsArrival(false)
	, mTotalCost(INIT_TOTAL_COST)
	, mAdvanceLevel(INIT_LEVEL)
	, mTotalDefeat(0)
	, mMousePos(tkl::Vector3::ZERO)
	, mClickPos(tkl::Vector3::ZERO)
	{}
	~GameParameter(){}

	void SetMapSize(int value){ mMapSize = value; }
	int GetMapSize() const { return mMapSize; }
	void SetMapRow(int value){ mMapRow = value; }
	int GetMapRow() const { return mMapRow; }
	void SetMapColumn(int value){ mMapColumn = value; }
	int GetMapColumn() const { return mMapColumn; }
	void SetIsArrival(bool value){ mIsArrival = value; }
	bool GetIsArrival() const { return mIsArrival; }
	void SetTotalCost(int value){ mTotalCost = value; }
	int GetTotalCost() const { return mTotalCost; }
	void SetAdvanceLevel(int value) { mAdvanceLevel = value; }
	int GetAdvenceLevel() const { return mAdvanceLevel; }
	void SetTotalDefeat(int value) { mTotalDefeat = value; }
	int GetTotalDefeat() const { return mTotalDefeat; }
	void SetMousePos(const tkl::Vector3& pos){ mMousePos = pos; }
	const tkl::Vector3& GetMousePos() { return mMousePos; }
	void SetClickPos(const tkl::Vector3& pos){ mClickPos = pos; }
	const tkl::Vector3& GetClickPos() { return mClickPos; }
	void SetFields(std::vector<std::vector<tkl::CELL>>& fields){ mFields = fields; }
	std::vector<std::vector<tkl::CELL>>& GetFields() { return mFields; }

private:
	int mMapSize;
	int mMapRow, mMapColumn;
	bool mIsArrival;
	int mTotalCost;
	int mAdvanceLevel;
	int mTotalDefeat;
	tkl::Vector3 mMousePos;
	tkl::Vector3 mClickPos;
	std::vector<std::vector<tkl::CELL>> mFields;
};

#endif