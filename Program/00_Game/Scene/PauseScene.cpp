//****************************************************************************
// ファイル名：PauseScene(ポーズ画面クラス)
// 作　成　日：2022/12/15
#include "PauseScene.h"

#include "SceneManager.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../02_Library/Input.h"

// ファイルパス
static constexpr const char* SOUND_FILE = "Resource/sound/cancel.wav";

PauseScene::PauseScene()
: mSndCancel(nullptr)
{}

PauseScene::~PauseScene()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化
// 引　数：なし
// 戻り値：なし
// 詳　細：初期化処理を行う
//****************************************************************************
void PauseScene::Initialize()
{
	mSndCancel = tkl::Sound::CreateSound(SOUND_FILE);
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void PauseScene::Update(float deltaTime)
{
	// 前のシーンに戻る
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_P)){
		mSndCancel->Play();
		SceneManager::GetInstance()->ReturnScene();
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：なし
// 戻り値：なし
// 詳　細：描画処理を行う
//****************************************************************************
void PauseScene::Draw()
{
	tkl::Font::DrawFontEx(0, 0, 32, tkl::Vector3(1, 1, 1), "PAUSED");
}