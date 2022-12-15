//****************************************************************************
// ファイル名：SceneBase(基底画面クラス)
// 作　成　日：2022/12/15
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include <memory>

class SceneManager;
class SceneBase
{
public:
	SceneBase(std::shared_ptr<SceneManager> manager)
	: mSceneManager(manager){}
	virtual ~SceneBase(){}
	
	virtual void Initialize(){}
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(){}

protected:
	std::shared_ptr<SceneManager> mSceneManager;
};

#endif