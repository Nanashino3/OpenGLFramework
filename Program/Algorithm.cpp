#include "Algorithm.h"

namespace tkl
{
std::list<NODE*> Algorithm::mOpenList = {};

// 経路探索
bool Algorithm::RouteSearch(int rowSize, int colSize, std::vector<std::vector<CELL>>& cells, std::vector<CELL>& route)
{
	// スタートとゴールのセル決め
	CELL start = {}, goal = {};
	for(int r = 0; r < rowSize; ++r){
		for(int c = 0; c < colSize; ++c){
			if(STATUS::START == cells[r][c].status) start = cells[r][c];
			if(STATUS::GOAL  == cells[r][c].status) goal  = cells[r][c];
		}
	}

	// 初期化
	std::vector<std::vector<NODE>> nodes;
	nodes.resize(rowSize);
	for(int r  = 0; r < rowSize; ++r){
		for(int c = 0; c < colSize; ++c){
			nodes[r].resize(colSize);

			nodes[r][c].cell = cells[r][c];
			nodes[r][c].heuristCost = abs(goal.column - c) + (goal.row - r);
		}
	}

	return ASter(rowSize, colSize, nodes, &nodes[start.row][start.column], route);
}

// A*アルゴリズム
bool Algorithm::ASter(int rowSize, int colSize, std::vector<std::vector<NODE>>& nodes, NODE* current, std::vector<CELL>& route)
{
	// 4方向探索
	CELL dirCell[] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };
	for(int i = 0; i < 4; ++i){
		int row	   = current->cell.row + dirCell[i].row;
		int column = current->cell.column + dirCell[i].column;

		// オープン可能か検査
		if(!IsPossibleOpen(rowSize, colSize, row, column, nodes)){ continue; }

		// ゴール判定を行う
		if(STATUS::GOAL == nodes[row][column].cell.status){
			route.emplace_back(nodes[row][column].cell);

			NODE* node = current;
			while(node != nullptr){
				route.emplace_back(node->cell);
				node = node->parent;
			}
			return true;
		}

		// 隣接ノードをオープンリストに追加する
		nodes[row][column].cell.status = STATUS::OPEN;
		nodes[row][column].parent = current;
		nodes[row][column].betweenCost = current->betweenCost + 1;
		nodes[row][column].totalCost = nodes[row][column].betweenCost + nodes[row][column].heuristCost;

		mOpenList.emplace_back(&nodes[row][column]);
	}
	// 探索が終了したので自分をクローズする
	if(STATUS::START != current->cell.status){ current->cell.status = STATUS::CLOSE; }

	// 次の探索ノードを取得する(オープン済リストから最小コスト)
	mOpenList.sort([](const NODE* a, const NODE* b){ return a->totalCost < b->totalCost;  });
	NODE* next = mOpenList.front();
	if(next){ mOpenList.erase(mOpenList.begin()); }

	// 再帰的に探索
	return ASter(rowSize, colSize, nodes, next, route);
}

bool Algorithm::IsPossibleOpen(int rowSize, int colSize, int row, int column, std::vector<std::vector<NODE>>& nodes)
{
	// 範囲検査
	if(row >= rowSize || row < 0) return false;
	if(column >= colSize || column < 0) return false;

	// 状態検査
	if(STATUS::EMPTY == nodes[row][column].cell.status) return true;
	if(STATUS::GOAL  == nodes[row][column].cell.status) return true;

	return false;
}

} // namespace tkl