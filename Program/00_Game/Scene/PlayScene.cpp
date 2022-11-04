#include "PlayScene.h"

#include "../../01_Engine/Font.h"

PlayScene::PlayScene()
{}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update()
{
	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	tkl::Font::DrawString(0, 0, "プレイシーン");

	return nextScene;
}