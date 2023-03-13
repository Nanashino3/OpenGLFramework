//****************************************************************************
// ファイル名：GameOverScene(ゲームオーバ画面クラス)
// 作　成　日：2023/1/9
#include "GameOverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Graphics/Canvas.h"

#include "../../01_Engine/Camera/ScreenCamera.h"

#include "../../02_Library/Input.h"

// 定数
static constexpr float PLAY_BTN_HEIGHT = 64.0f;
static constexpr float EXIT_BTN_HEIGHT = 128.0f;

GameOverScene::GameOverScene()
: m2DCam(nullptr)
, mCanvas(nullptr)
{}

GameOverScene::~GameOverScene()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化
// 引　数：なし
// 戻り値：なし
// 詳　細：初期化処理を行う
//****************************************************************************
void GameOverScene::Initialize()
{
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// UI描画とボタンの生成
	mCanvas = std::make_shared<tkl::Canvas>();
	mCanvas->AddButton("Title", tkl::Vector3(0.0f, -PLAY_BTN_HEIGHT, 0.0f), [this]() {
		SceneManager::GetInstance()->LoadScene(std::make_shared<TitleScene>());
	});
	mCanvas->AddButton("Exit", tkl::Vector3(0.0f, -EXIT_BTN_HEIGHT, 0.0f), [this]() {
		exit(1);
	});
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void GameOverScene::Update(float deltaTime)
{
	m2DCam->Update();
	mCanvas->Update();
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：なし
// 戻り値：なし
// 詳　細：描画処理を行う
//****************************************************************************
void GameOverScene::Draw()
{
	tkl::Font::DrawFontEx(0.0f, 0.0f, 64, tkl::Vector3(1.0f, 0.0f, 0.0f), "GAME OVER");
	mCanvas->Draw(m2DCam);
}