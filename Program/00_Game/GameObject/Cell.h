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
	const int PLANE_SIZE = 50;
	const int BLOCK_SIZE = 30;
	const char* TEXTURE_FIELD = "Resource/panel_soil.bmp";
	const char* TEXTURE_BLOCK = "Resource/panel_grass.bmp";
	const char* TEXTURE_CURSOR = "Resource/debug/test2.bmp";
public:
	Cell(std::shared_ptr<Parameter> param);
	virtual ~Cell();

	virtual void Initialize() final;
	virtual void Collision() final;
	virtual void Draw() final;

	void SetCellInfo(const tkl::CELL& info){ mCellInfo = info; }
	const tkl::CELL& GetCellInfo() { return mCellInfo; }

private:
	tkl::CELL mCellInfo;
	std::vector<std::shared_ptr<tkl::Mesh>> mMeshList;
//	std::shared_ptr<tkl::Mesh> mMesh;
	std::shared_ptr<tkl::Mesh> mCursor;
	std::shared_ptr<GameParameter> mParam;
};

#endif