//****************************************************************************
// ファイル名：Cell(マスクラス)
// 作　成　日：2022/12/17
#ifndef _CELL_H_
#define _CELL_H_

#include "GameObject.h"
#include "../../01_Engine/Algorithm.h"

class GameParameter;
namespace tkl{ class Mesh; }

class Cell : public GameObject
{
public:
	Cell(std::shared_ptr<Parameter> param);
	virtual ~Cell();

	void Initialize(const tkl::CELL& cell);

	virtual void Collision() final;
	virtual void Draw() final;

	void SetCellInfo(const tkl::CELL& cell){ mCell = cell; }
	const tkl::CELL& GetCellInfo() { return mCell; }

private:
	tkl::CELL mCell;
	std::vector<std::shared_ptr<tkl::Mesh>> mMeshList;
	std::shared_ptr<tkl::Mesh> mCursor;
	std::shared_ptr<GameParameter> mParam;
	bool mIsSelecting;
};

#endif