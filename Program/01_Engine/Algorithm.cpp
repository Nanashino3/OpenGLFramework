//****************************************************************************
// ファイル名：Algorithm(アルゴリズムクラス)
// 作　成　日：2022/11/24
#include "Algorithm.h"

namespace tkl
{
std::list<NODE*> Algorithm::sOpenList = {};

//****************************************************************************
// 関数名：RouteSearch
// 概　要：経路探索
// 引　数：arg1 行サイズ
//       ：arg2 列サイズ
//       ：arg3 セル配列
//       ：arg4 探索後のルート
// 戻り値：[探索成功 : true]   [探索失敗 : false]
// 詳　細：
//****************************************************************************
bool Algorithm::RouteSearch(int rowSize, int colSize, std::vector<std::vector<CELL>>& cells, std::vector<CELL>& route)
{
	route.clear();
	sOpenList.clear();

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
			nodes[r][c].heuristCost = abs(goal.column - c) + abs(goal.row - r);
		}
	}
	return ASter(rowSize, colSize, nodes, &nodes[start.row][start.column], route);
}

//****************************************************************************
// 関数名：ASter(private)
// 概　要：A*アルゴリズム
// 引　数：arg1 行サイズ
//       ：arg2 列サイズ
//       ：arg3 探索するためのノード
//       ：arg4 探索中のノード
//       ：arg5 探索後のルート
// 戻り値：[探索成功 : true]   [探索失敗 : false]
// 詳　細：
//****************************************************************************
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

		sOpenList.emplace_back(&nodes[row][column]);
	}
	// 探索が終了したので自分をクローズする
	if(STATUS::START != current->cell.status){ current->cell.status = STATUS::CLOSE; }

	// 次の探索ノードを取得する(オープン済リストから最小コスト)
	if(sOpenList.empty()){ return false; }
	sOpenList.sort([](const NODE* a, const NODE* b){ return a->totalCost < b->totalCost;  });
	NODE* next = sOpenList.front();
	if(next){ sOpenList.erase(sOpenList.begin()); }

	// 再帰的に探索
	return ASter(rowSize, colSize, nodes, next, route);
}

//****************************************************************************
// 関数名：IsPossibleOpen(private)
// 概　要：オープン可能か
// 引　数：arg1 行サイズ
//       ：arg2 列サイズ
//       ：arg3 探索の行
//       ：arg4 探索の列
//       ：arg5 探索するためのノード
// 戻り値：[探索可能 : true]   [探索不能 : false]
// 詳　細：
//****************************************************************************
bool Algorithm::IsPossibleOpen(int rowSize, int colSize, int row, int column, std::vector<std::vector<NODE>>& nodes)
{
	// 範囲検査
	if(row >= rowSize || row < 0){ return false; }
	if(column >= colSize || column < 0){ return false; }

	// 状態検査
	if(nodes[row][column].cell.status == STATUS::EDITABLE){ return true; }
	if(nodes[row][column].cell.status == STATUS::UNEDITABLE){ return true; }
	if(nodes[row][column].cell.status == STATUS::GOAL){ return true; }

	return false;
}

} // namespace tkl