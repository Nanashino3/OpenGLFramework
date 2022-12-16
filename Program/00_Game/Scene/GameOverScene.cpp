#include "GameOverScene.h"

#include "TitleScene.h"
#include "SceneManager.h"
#include "../../01_Engine/Font.h"
#include "../../02_Library/Input.h"

GameOverScene::GameOverScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{}

GameOverScene::~GameOverScene()
{}

void GameOverScene::Initialize()
{}

void GameOverScene::Update(float deltaTime)
{
	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_ENTER)){
		mSceneManager->LoadScene<TitleScene>();
	}
}

void GameOverScene::Draw()
{
	tkl::Font::DrawStringEx(0, 0, "�Q�[���I�[�o���");
}