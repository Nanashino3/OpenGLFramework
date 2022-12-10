#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include <vector>
#include <list>
#include "BaseScene.h"
#include "../../02_Library/Vector.h"
#include "../../01_Engine/Algorithm.h"

// ‘O•ûéŒ¾
class Field;
class GameObject;
class GameParameter;
namespace tkl{
class Mesh;
class Camera;
}

class PlayScene : public BaseScene, public std::enable_shared_from_this<PlayScene>
{
public:
	PlayScene();
	virtual ~PlayScene();

	virtual std::shared_ptr<BaseScene> Update(float deltaTime) final;

private:
	float mElapsed;
	std::shared_ptr<GameParameter> mParam;
	std::shared_ptr<tkl::Camera> mCamera;
	std::shared_ptr<Field> mField;
};
#endif