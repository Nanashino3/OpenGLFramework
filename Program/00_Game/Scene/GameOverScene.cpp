#include "GameOverScene.h"

#include "TitleScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Graphics/Font.h"
#include "../../02_Library/Input.h"

// ファイルパス
static constexpr const char* SOUND_FILE = "Resource/sound/decide.wav";

GameOverScene::GameOverScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
, mSndDecide(nullptr)
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
		mSceneManager->LoadScene(std::make_shared<TitleScene>(mSceneManager));
	}
}

void GameOverScene::Draw()
{
	tkl::Font::DrawFontEx(0, 0, 32, tkl::Vector3(0, 0, 0), "GAME OVER");
}