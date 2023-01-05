//****************************************************************************
// ファイル名：TitleScene(タイトル画面クラス)
// 作　成　日：2022/12/15
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneManager.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Font.h"
#include "../../01_Engine/Graphics/Canvas.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Camera/ScreenCamera.h"
#include "../../01_Engine/Camera/FixedCamera.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Math.h"

static constexpr const char* DECIDE_FILE = "Resource/sound/decide.wav";
static constexpr const char* TEXTURE_FILE = "Resource/texture/img_title.jpg";
static constexpr const char* MODEL_FILE = "Resource/model/earth/earth.obj";

TitleScene::TitleScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
{
	mSndDecide = tkl::Sound::CreateSound(DECIDE_FILE);
	mTexMesh = tkl::Mesh::CreateMeshForSprite();
	mTexMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));

	// カメラ関連生成
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);
	m3DCam = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	m3DCam->SetPosition(tkl::Vector3(0, 0, 50));

	// UI描画とボタンの生成
	mCanvas = std::make_shared<tkl::Canvas>();
	mCanvas->AddButton("Play", tkl::Vector3(0, -64, 0), [this](){ 
		mSndDecide->Play();
		mSceneManager->LoadScene<GameScene>();
	});
	mCanvas->AddButton("Exit", tkl::Vector3(0, -128, 0), [this](){
		mSndDecide->Play();
		exit(1);
	});

	mModel = tkl::Model::CreateModelFromObjFile(MODEL_FILE);
	mModel->SetScale(tkl::Vector3(15, 15, 15));
	mModel->SetPosition(tkl::Vector3(0, 10, 0));
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
	m2DCam->Update();
	m3DCam->Update();
	mCanvas->Update();

	tkl::Quaternion rot = mModel->GetRotation();
	rot *= tkl::Quaternion::RotationAxis({0, 1, 0}, tkl::ToRadian(0.1f));
	mModel->SetRotation(rot);
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
	mTexMesh->Draw(m2DCam);
	mModel->Draw(m3DCam);

	tkl::Font::DrawFontEx(0, 192, 64, tkl::Vector3(1, 1, 1), "SPACE");
	tkl::Font::DrawFontEx(0,  64, 64, tkl::Vector3(1, 1, 1), "DEFENDER");
	mCanvas->Draw(m2DCam);
}