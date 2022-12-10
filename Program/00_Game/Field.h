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
public:
	Field(std::shared_ptr<GameParameter> param);
	~Field();

	void Update(std::shared_ptr<GameParameter> param);

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