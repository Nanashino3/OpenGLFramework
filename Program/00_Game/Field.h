//****************************************************************************
// ファイル名：Field(フィールドクラス)
// 作　成　日：2022/12/11
#ifndef _FIELD_H_
#define _FIELD_H_

#include <memory>
#include "../01_Engine/Algorithm.h"

class GameParameter;
namespace tkl{
class Mesh;
}

class Field
{
	const int MAP_SIZE = 50;
public:
	Field(std::shared_ptr<GameParameter> param);
	~Field();

	void Update(std::shared_ptr<GameParameter> param);
	void Draw(std::shared_ptr<GameParameter> param);

private:
	void PriSelectField(std::shared_ptr<GameParameter> param, const tkl::Vector3& pos);

private:
	int mScreenW, mScreenH;
	float mStartPosX, mStartPosZ;
	std::shared_ptr<tkl::Mesh> mCursor;
	std::shared_ptr<tkl::Mesh> mGrid;
	std::vector<std::vector<tkl::CELL>> mFields;
};

#endif