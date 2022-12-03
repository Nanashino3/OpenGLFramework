#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include <vector>
#include <list>
#include "BaseScene.h"
#include "../../02_Library/Vector.h"
#include "../../01_Engine/Algorithm.h"

namespace tkl{
class Camera;
class Mesh;
}

class AdvanceUnit;

class PlayScene : public BaseScene, public std::enable_shared_from_this<PlayScene>
{
public:
	enum class MODE
	{
		EDIT_MODE,
		PLAY_MODE
	};
	PlayScene();
	virtual ~PlayScene();

	virtual std::shared_ptr<BaseScene> Update(float deltaTime) final;

private:
	void PriDrawSelectField(const tkl::Vector3& pos);

private:
	int mScreenW, mScreenH;
	float mFirstPosX, mFirstPosZ;
	int mRouteCount;
	MODE mMode;

	std::shared_ptr<tkl::Camera> mCamera;
	std::shared_ptr<tkl::Mesh> mCursor;

	std::list<std::shared_ptr<AdvanceUnit>> mAdvanceList;

	std::vector<tkl::CELL> mRoute;
	std::vector<std::vector<tkl::CELL>> mFields;
	std::vector<std::shared_ptr<tkl::Mesh>> mObstacles;

	std::shared_ptr<tkl::Mesh> mGrid;
};
#endif