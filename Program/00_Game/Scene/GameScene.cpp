//****************************************************************************
// ファイル名：GameScene(ゲーム画面クラス)
// 作　成　日：2022/12/15
#include "GameScene.h"

#include "PauseScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"

#include "../Field.h"
#include "../GameObject/Cell.h"
#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/GameParameter.h"
#include "../GameObject/ObjectManager.h"

#include "../NotifyService/Notifier.h"
#include "../NotifyService/AdvanceUnitObserver.h"
#include "../NotifyService/DefenseUnitObserver.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Camera/FixedCamera.h"
#include "../../01_Engine/Camera/ScreenCamera.h"
#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/Graphics/Font.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Utility.h"

static constexpr int MAX_CREATE = 5;
static constexpr int MAX_DURABILITY = 1;
static constexpr const char* BGM_FILE = "Resource/sound/gamebgm.wav";
static constexpr const char* PAUSE_SE_FILE = "Resource/sound/pause.wav";

GameScene::GameScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
, mElapsed(0)
, mDurability(MAX_DURABILITY)
, mParam(nullptr)
, m3DCam(nullptr), m2DCam(nullptr)
, mbgTex(nullptr)
, mField(nullptr)
, mSndBgm(nullptr)
{
	mSndBgm = tkl::Sound::CreateSound(BGM_FILE);
	mSndPause = tkl::Sound::CreateSound(PAUSE_SE_FILE);
}

GameScene::~GameScene()
{
	ObjectManager::GetInstance()->DestroyInstance();
	Notifier::GetInstance()->DestroyInstance();
}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化
// 引　数：なし
// 戻り値：なし
// 詳　細：初期化処理を行う
//****************************************************************************
void GameScene::Initialize()
{
	// ウィンドウサイズを取得
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);

	// 3Dカメラ生成
	m3DCam = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	m3DCam->SetPosition(tkl::Vector3(0, 350, 180));

	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// パラメータ生成
	mParam = std::make_shared<GameParameter>();
	mParam->SetCamera(m3DCam);

	// フィールド生成
	mField = std::make_shared<Field>(mParam);

	mbgTex = tkl::Mesh::CreateMeshForSprite();
	mbgTex->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/img_play.jpg"));

	// オブザーバー登録
	Notifier::GetInstance()->AddObserver(std::make_shared<AdvanceUnitObserver>());
	Notifier::GetInstance()->AddObserver(std::make_shared<DefenseUnitObserver>());
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void GameScene::Update(float deltaTime)
{
	// TODO：暫定で耐久を設ける
	if(mDurability == 0){
		mSceneManager->CallScene<GameOverScene>();
		mSndBgm->Stop();
		return;
	}
	if(!mSndBgm->IsPlay()){ mSndBgm->Play(); }

	// カメラ更新
	m3DCam->Update();
	m2DCam->Update();
	mParam->SetDeltaTime(deltaTime);

	if(mParam->GetIsArrival()){
		if(mDurability != 0){ mDurability -= 1; }
		mParam->SetIsArrival(false);
	}

	// 進軍ユニット
	mElapsed += deltaTime;
	if(mElapsed > 5.0f){
		mElapsed = 0;

		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		if(list->size() != MAX_CREATE){
			// 進軍ユニット生成
			auto newUnit = ObjectManager::GetInstance()->Create<AdvanceUnit>(mParam);
			newUnit->Initialize();
		}
	}

	// フィールドの更新
	mField->Update();

	// オブジェクトの衝突判定
	ObjectManager::GetInstance()->Collision();

	// オブジェクトの更新処理
	ObjectManager::GetInstance()->Update();

	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_P)){
		mSceneManager->CallScene<PauseScene>();
		mSndPause->Play();
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：なし
// 戻り値：なし
// 詳　細：描画処理を行う
//****************************************************************************
void GameScene::Draw()
{
	mbgTex->Draw(m2DCam);

	tkl::Font::DrawStringEx(0,   0, tkl::Vector3(1, 1, 1), "耐久度 : %d", mDurability);
	tkl::Font::DrawStringEx(0,  50, tkl::Vector3(1, 1, 1), "残金 : %d", mParam->GetTotalCost());
	tkl::Font::DrawStringEx(0, 100, tkl::Vector3(1, 1, 1), "進軍レベル : %2d", mParam->GetAdvenceLevel());

	// フィールドの更新
	mField->Draw();

	// オブジェクトの描画処理
	ObjectManager::GetInstance()->Draw();
}