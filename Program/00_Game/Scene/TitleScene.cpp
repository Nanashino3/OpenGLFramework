//****************************************************************************
// ファイル名：TitleScene(タイトル画面クラス)
// 作　成　日：2022/12/15
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneManager.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Font/Font.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../01_Engine/Graphics/Canvas.h"

#include "../../01_Engine/Camera/ScreenCamera.h"
#include "../../01_Engine/Camera/FixedCamera.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Math.h"

// ファイルパス
static constexpr const char* TEXTURE_FILE = "Resource/texture/img_title.jpg";
static constexpr const char* MODEL_FILE = "Resource/model/earth/earth.obj";

// 定数
static constexpr float CAMERA_POS_Z = 50.0f;
static constexpr float MODEL_SIZE = 15.0f;
static constexpr float MODEL_HEIGHT = 10.0f;
static constexpr float PLAY_BTN_HEIGHT = 64.0f;
static constexpr float EXIT_BTN_HEIGHT = 128.0f;

TitleScene::TitleScene()
: mModel(nullptr)
, mTexMesh(nullptr)
, m3DCam(nullptr), m2DCam(nullptr)
, mCanvas(nullptr)
{}

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
{
	mTexMesh = tkl::Mesh::CreateMeshForSprite();
	mTexMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));

	// カメラ関連生成
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);
	m3DCam = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	m3DCam->SetPosition(tkl::Vector3(0.0f, 0.0f, CAMERA_POS_Z));

	// UI描画とボタンの生成
	mCanvas = std::make_shared<tkl::Canvas>();
	mCanvas->AddButton("Play", tkl::Vector3(0.0f, -PLAY_BTN_HEIGHT, 0.0f), [this]() {
		SceneManager::GetInstance()->LoadScene(std::make_shared<GameScene>());
	});
	mCanvas->AddButton("Exit", tkl::Vector3(0.0f, -EXIT_BTN_HEIGHT, 0.0f), [this]() {
		exit(1);
	});

	mModel = tkl::Model::CreateModelFromObjFile(MODEL_FILE);
	mModel->SetScale(tkl::Vector3(MODEL_SIZE, MODEL_SIZE, MODEL_SIZE));
	mModel->SetPosition(tkl::Vector3(0.0f, MODEL_HEIGHT, 0.0f));
}

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
	rot *= tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(0.1f));
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

	tkl::Font::DrawFontEx(0.0f, 192, 64, tkl::Vector3(1.0f, 1.0f, 1.0f), "SPACE");
	tkl::Font::DrawFontEx(0.0f,  64, 64, tkl::Vector3(1.0f, 1.0f, 1.0f), "DEFENDER");
	mCanvas->Draw(m2DCam);
}