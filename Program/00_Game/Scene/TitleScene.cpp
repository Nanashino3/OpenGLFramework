//****************************************************************************
// ファイル名：TitleScene(タイトル画面クラス)
// 作　成　日：2022/12/15
#include "TitleScene.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../02_Library/Input.h"

TitleScene::TitleScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{
	mSndDecide = tkl::Sound::CreateSound("Resource/sound/decide.wav");
}

TitleScene::~TitleScene()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化
// 引　数：なし
// 戻り値：なし
// 詳　細：初期化処理を行う
//****************************************************************************
void TitleScene::Initialize()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void TitleScene::Update(float deltaTime)
{
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_ENTER)){
		mSceneManager->LoadScene<GameScene>();
		mSndDecide->Play();
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：なし
// 戻り値：なし
// 詳　細：描画処理を行う
//****************************************************************************
void TitleScene::Draw()
{
	tkl::Font::DrawStringEx(0, 0, "タイトル画面");
}