#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_
#include <vector>
#include <list>
#include "../02_Library/Vector.h"

namespace tkl
{
class Algorithm
{
public:
	enum class STATUS {
		OPEN,		// オープン
		CLOSE,		// クローズ
		START,		// スタート
		GOAL,		// ゴール
		EDITABLE,	// 編集可
		UNIT,		// ユニット
	};

	struct CELL
	{
		int row;		// 行
		int column;		// 列
		STATUS status;	// マスの状態
	};

	struct NODE
	{
		CELL cell;			// セル
		NODE* parent;		// 親ノード
		int heuristCost;	// 推定コスト
		int betweenCost;	// ノード間コスト
		int totalCost;		// 総コスト
	};

	// 経路探索
	static bool RouteSearch(int rowSize, int colSize, std::vector<std::vector<CELL>>& cells, std::vector<CELL>& route);

private:
	static bool ASter(int rowSize, int colSize, std::vector<std::vector<NODE>>& nodes, NODE* current, std::vector<CELL>& route);
	static bool IsPossibleOpen(int rowSize, int colSize, int row, int column, std::vector<std::vector<NODE>>& nodes);

private:
	static std::list<NODE*> sOpenList;
};

using STATUS = tkl::Algorithm::STATUS;
using CELL = tkl::Algorithm::CELL;
using NODE = tkl::Algorithm::NODE;

}

#endif