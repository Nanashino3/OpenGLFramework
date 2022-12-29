//****************************************************************************
// ファイル名：TitleScene(タイトル画面クラス)
// 作　成　日：2022/12/15
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "SceneBase.h"
namespace tkl{
class Mesh;
class Camera;
class Sound;
}
class TitleScene : public SceneBase
{
public:
	TitleScene(std::shared_ptr<SceneManager> manager);
	virtual ~TitleScene();

	virtual void Initialize() final;
	virtual void Update(float deltaTime) final;
	virtual void Draw() final;

private:
	std::shared_ptr<tkl::Sound> mSndDecide;
	std::shared_ptr<tkl::Mesh> mTexMesh;
	std::shared_ptr<tkl::Camera> mCamera;
};

#endif