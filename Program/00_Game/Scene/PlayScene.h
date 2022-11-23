#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_
#include "BaseScene.h"
#include "../../02_Library/Vector.h"
#include <vector>

namespace tkl{
class Camera;
class Mesh;
}
class PlayScene : public BaseScene, public std::enable_shared_from_this<PlayScene>
{
public:
	PlayScene();
	virtual ~PlayScene();

	virtual std::shared_ptr<BaseScene> Update(float deltaTime) final;

private:
	void PriDrawSelectField(const tkl::Vector3& pos);

private:
	struct Field
	{
		tkl::Vector3 pos;
		Field* parent;
	};

	int mScreenW, mScreenH;

	std::shared_ptr<tkl::Camera> mCamera;
	std::shared_ptr<tkl::Mesh> mGrid;
	std::shared_ptr<tkl::Mesh> mCursor;

	std::vector<std::vector<Field>> mFields;
};
#endif