#include "PauseScene.h"

#include "SceneManager.h"
#include "../../01_Engine/Font.h"
#include "../../02_Library/Input.h"

PauseScene::PauseScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{}

PauseScene::~PauseScene()
{}

void PauseScene::Initialize()
{}

void PauseScene::Update(float deltaTime)
{
	// 前のシーンに戻る
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_B)){
		mSceneManager->ReturnScene();
	}
}

void PauseScene::Draw()
{
	tkl::Font::DrawStringEx(0, 50, "ポーズ画面");
}