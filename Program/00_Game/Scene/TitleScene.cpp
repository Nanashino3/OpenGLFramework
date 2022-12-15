#include "TitleScene.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Font.h"
#include "../../02_Library/Input.h"

TitleScene::TitleScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{}

TitleScene::~TitleScene()
{}

void TitleScene::Initialize()
{}

void TitleScene::Update(float deltaTime)
{
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_ENTER)){
		mSceneManager->LoadScene<GameScene>();
	}
}

void TitleScene::Draw()
{
	tkl::Font::DrawStringEx(0, 0, "ƒ^ƒCƒgƒ‹‰æ–Ê");
}