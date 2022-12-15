#include "GameScene.h"

#include "PauseScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Font.h"
#include "../../02_Library/Input.h"

GameScene::GameScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{}

GameScene::~GameScene()
{}

void GameScene::Initialize()
{}

void GameScene::Update(float deltaTime)
{
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_P)){
		mSceneManager->LoadScene<PauseScene>();
	}
}

void GameScene::Draw()
{
	tkl::Font::DrawStringEx(0, 0, "ÉQÅ[ÉÄâÊñ ");
}