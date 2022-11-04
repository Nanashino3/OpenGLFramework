#include "TitleScene.h"

#include "PlayScene.h"
#include "../../01_Engine/Font.h"
#include "../../02_Library/Input.h"

TitleScene::TitleScene()
{}

TitleScene::~TitleScene()
{}

std::shared_ptr<BaseScene> TitleScene::Update(float deltaTime)
{
	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	tkl::Font::DrawString(0, 0, "タイトルシーン");
	if(tkl::Input::IsKeyDownTrigger(eKeys::KB_ENTER)){
		nextScene = std::make_shared<PlayScene>();
	}

	return nextScene;
}