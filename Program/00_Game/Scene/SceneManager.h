//****************************************************************************
// ファイル名：SceneManager(画面管理クラス)
// 作　成　日：2022/12/15
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <memory>
#include <stack>
#include "SceneBase.h"

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
	
	//****************************************************************************
	// 関数名：LoadScene
	// 概　要：画面の読み込み
	// 引　数：なし
	// 戻り値：なし
	// 詳　細：指定した新しい画面を読み込む
	//****************************************************************************
	template <class T>
	void LoadScene()
	{
		while(!mPrevScene.empty()){ mPrevScene.pop(); }
		mNextScene = std::make_shared<T>(shared_from_this());
		mNextScene->Initialize();
	}

	//****************************************************************************
	// 関数名：CallScene
	// 概　要：画面の呼び出し
	// 引　数：なし
	// 戻り値：なし
	// 詳　細：指定した画面を呼び出す(モーダルに近い)
	//****************************************************************************
	template <class T>
	void CallScene()
	{
		if(mNowScene) mPrevScene.push(mNowScene);
		mNextScene = std::make_shared<T>(shared_from_this());
		mNextScene->Initialize();
	}

	// 元のシーンに戻る
	void ReturnScene();
	
	// シーンの更新をする
	void SceneUpdate(float deltaTime);

private:
	std::shared_ptr<SceneBase> mNextScene;
	std::shared_ptr<SceneBase> mNowScene;
	std::stack<std::shared_ptr<SceneBase>> mPrevScene;
};

#endif