#include "GameOverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Graphics/Canvas.h"

#include "../../01_Engine/Camera/ScreenCamera.h"

#include "../../02_Library/Input.h"

// ’è”
static constexpr float PLAY_BTN_HEIGHT = 64.0f;
static constexpr float EXIT_BTN_HEIGHT = 128.0f;

GameOverScene::GameOverScene()
: m2DCam(nullptr)
, mCanvas(nullptr)
{}

GameOverScene::~GameOverScene()
{}

void GameOverScene::Initialize()
{
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// UI•`‰æ‚Æƒ{ƒ^ƒ“‚Ì¶¬
	mCanvas = std::make_shared<tkl::Canvas>();
	mCanvas->AddButton("Title", tkl::Vector3(0.0f, -PLAY_BTN_HEIGHT, 0.0f), [this]() {
		SceneManager::GetInstance()->LoadScene(std::make_shared<TitleScene>());
	});
	mCanvas->AddButton("Exit", tkl::Vector3(0.0f, -EXIT_BTN_HEIGHT, 0.0f), [this]() {
		exit(1);
	});
}

void GameOverScene::Update(float deltaTime)
{
	m2DCam->Update();
	mCanvas->Update();
}

void GameOverScene::Draw()
{
	tkl::Font::DrawFontEx(0, 0, 32, tkl::Vector3(0, 0, 0), "GAME OVER");
	mCanvas->Draw(m2DCam);
}