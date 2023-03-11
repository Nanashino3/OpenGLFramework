//****************************************************************************
// ファイル名：SceneManager(画面管理クラス)
// 作　成　日：2022/12/15
#include "SceneManager.h"
#include "../../02_Library/Utility.h"

SceneManager* SceneManager::sMyInstance = nullptr;
SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

SceneManager* SceneManager::GetInstance()
{
	if(!sMyInstance){ sMyInstance = new SceneManager(); }
	return sMyInstance;
}

void SceneManager::DestoryInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// 関数名：LoadScene
// 概　要：画面の読み込み
// 引　数：なし
// 戻り値：なし
// 詳　細：指定した新しい画面を読み込む
//****************************************************************************
void SceneManager::LoadScene(std::shared_ptr<SceneBase> nextScene)
{
	while (!mPrevScene.empty()){ mPrevScene.pop(); }
	mNextScene = nextScene;
	mNextScene->Initialize();
}

//****************************************************************************
// 関数名：CallScene
// 概　要：画面の呼び出し
// 引　数：なし
// 戻り値：なし
// 詳　細：指定した画面を呼び出す(モーダルに近い)
//****************************************************************************
void SceneManager::CallScene(std::shared_ptr<SceneBase> nextScene)
{
	if (mNowScene){ mPrevScene.push(mNowScene); }
	mNextScene = nextScene;
	mNextScene->Initialize();
}

//****************************************************************************
// 関数名：ReturnScene
// 概　要：画面を戻す
// 引　数：なし
// 戻り値：なし
// 詳　細：遷移前の画面に戻る
//****************************************************************************
void SceneManager::ReturnScene()
{
	if(mPrevScene.empty()){ return; }
	mNextScene = mPrevScene.top();
	mPrevScene.pop();
}

//****************************************************************************
// 関数名：SceneUpdate
// 概　要：画面の更新
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：画面の更新を行う
//****************************************************************************
void SceneManager::SceneUpdate(float deltaTime)
{
	// シーンのインスタンスを更新
	if(mNextScene != nullptr){
		if(mNowScene != mNextScene){
			mNowScene = mNextScene;
			mNextScene = nullptr;
		}
	}

	if(!mPrevScene.empty()){
		std::shared_ptr<SceneBase> prevScene = mPrevScene.top();
		prevScene->Draw();
	}

	// 現在のシーンの処理
	mNowScene->Update(deltaTime);
	mNowScene->Draw();
}