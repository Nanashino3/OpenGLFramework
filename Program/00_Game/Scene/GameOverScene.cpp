#include "GameOverScene.h"

#include "TitleScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../02_Library/Input.h"

// ファイルパス
static constexpr const char* SOUND_FILE = "Resource/sound/decide.wav";

GameOverScene::GameOverScene()
: mSndDecide(nullptr)
{}

GameOverScene::~GameOverScene()
{}

void GameOverScene::Initialize()
{
	mSndDecide = tkl::Sound::CreateSound(SOUND_FILE);
}

void GameOverScene::Update(float deltaTime)
{
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_ENTER)){
		mSndDecide->Play();
		SceneManager::GetInstance()->LoadScene(std::make_shared<TitleScene>());
	}
}

void GameOverScene::Draw()
{
	tkl::Font::DrawFontEx(0, 0, 32, tkl::Vector3(0, 0, 0), "GAME OVER");
}