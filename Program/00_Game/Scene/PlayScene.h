#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_
#include "BaseScene.h"

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
	std::shared_ptr<tkl::Mesh> mPlane;
	std::shared_ptr<tkl::Camera> mCamera;
	std::shared_ptr<tkl::Mesh> mGrid;
};
#endif