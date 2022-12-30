//****************************************************************************
// ファイル名：TitleScene(タイトル画面クラス)
// 作　成　日：2022/12/15
#include "TitleScene.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "../../01_Engine/System.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Font.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Camera/ScreenCamera.h"
#include "../../02_Library/Input.h"

static constexpr const char* DECIDE_FILE = "Resource/sound/decide.wav";
static constexpr const char* TEXTURE_FILE = "Resource/texture/img_title.jpg";

TitleScene::TitleScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{
	mSndDecide = tkl::Sound::CreateSound(DECIDE_FILE);
	mTexMesh = tkl::Mesh::CreateMeshForSprite();
	mTexMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));

	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	mCamera = std::make_shared<tkl::ScreenCamera>(screenW, screenH);
}

TitleScene::~TitleScene()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化
// 引　数：なし
// 戻り値：なし
// 詳　細：初期化処理を行う
//****************************************************************************
void TitleScene::Initialize()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void TitleScene::Update(float deltaTime)
{
	mCamera->Update();

	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_ENTER)){
		mSceneManager->LoadScene<GameScene>();
		mSndDecide->Play();
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：なし
// 戻り値：なし
// 詳　細：描画処理を行う
//****************************************************************************
void TitleScene::Draw()
{
	mTexMesh->Draw(mCamera);
	tkl::Font::DrawStringEx(0, 0, tkl::Vector3(1, 1, 1), "タイトル画面");
}