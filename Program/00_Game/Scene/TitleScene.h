//****************************************************************************
// ファイル名：TitleScene(タイトル画面クラス)
// 作　成　日：2022/12/15
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "SceneBase.h"
namespace tkl{
class Mesh;
class Model;
class Camera;
class Canvas;
}
class TitleScene : public SceneBase
{
public:
	TitleScene(std::shared_ptr<SceneManager> manager);
	virtual ~TitleScene();

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	std::shared_ptr<tkl::Model> mModel;
	std::shared_ptr<tkl::Mesh> mTexMesh;
	std::shared_ptr<tkl::Camera> m3DCam;
	std::shared_ptr<tkl::Camera> m2DCam;
	std::shared_ptr<tkl::Canvas> mCanvas;
};

#endif