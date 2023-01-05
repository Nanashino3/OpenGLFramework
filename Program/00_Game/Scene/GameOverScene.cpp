#include "GameOverScene.h"

#include "TitleScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Graphics/Font.h"
#include "../../02_Library/Input.h"

GameOverScene::GameOverScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{
	mSndDecide = tkl::Sound::CreateSound("Resource/sound/decide.wav");
}

GameOverScene::~GameOverScene()
{}

void GameOverScene::Initialize()
{}

void GameOverScene::Update(float deltaTime)
{
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_ENTER)){
		mSceneManager->LoadScene<TitleScene>();
		mSndDecide->Play();
	}
}

void GameOverScene::Draw()
{
	tkl::Font::DrawFontEx(0, 0, 32, tkl::Vector3(1, 1, 1), "GAME OVER");
}