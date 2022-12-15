//****************************************************************************
// ファイル名：GameScene(ゲーム画面クラス)
// 作　成　日：2022/12/15
#include "GameScene.h"

#include "PauseScene.h"
#include "SceneManager.h"

#include "../Field.h"
#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/GameParameter.h"
#include "../GameObject/ObjectManager.h"

#include "../NotifyService/Notifier.h"
#include "../NotifyService/AdvanceUnitObserver.h"
#include "../NotifyService/DefenseUnitObserver.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/Camera/FixedCamera.h"
#include "../../02_Library/Input.h"

GameScene::GameScene(std::shared_ptr<SceneManager> manager)
: SceneBase(manager)
, mCamera(nullptr)
, mElapsed(0)
{}

GameScene::~GameScene()
{}

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
	mCamera = std::make_shared<tkl::FixedCamera>(screenW, screenH);
	mCamera->SetPosition(tkl::Vector3(0, 400, 200));

	// パラメータ生成
	mParam = std::make_shared<GameParameter>();

	// フィールド生成
	mField = std::make_shared<Field>(mParam);

	// オブザーバー登録
	Notifier::GetInstance()->AddObserver(std::make_shared<AdvanceUnitObserver>());
	Notifier::GetInstance()->AddObserver(std::make_shared<DefenseUnitObserver>());

	mEndurance = 1;
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
	if(mEndurance == 0){ return; }

	// カメラ更新
	mCamera->Update();
	mParam->SetCamera(mCamera);
	mParam->SetDeltaTime(deltaTime);

	tkl::Font::DrawStringEx(0, 100, "耐久値：%d", mEndurance);
	tkl::Font::DrawStringEx(0, 50, "DeltaTime：%f", deltaTime);
	tkl::Font::DrawStringEx(0, 150, "残金：%d", mParam->GetTotalCost());

	if (mParam->GetIsArrival()) {
		if (mEndurance != 0) mEndurance -= 1;
		mParam->SetIsArrival(false);
	}

	// 進軍ユニット
	mElapsed += deltaTime;
	if (mElapsed > 5.0f) {
		mElapsed = 0;

		auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
		if (list->size() != CREATE_MAX) {
			// 進軍ユニット生成
			auto newUnit = ObjectManager::GetInstance()->Create<AdvanceUnit>(mParam);
			newUnit->Initialize();
		}
	}

	// フィールドの更新
	mField->Update(mParam);

	// オブジェクトの衝突判定
	ObjectManager::GetInstance()->Collision();
	// オブジェクトの更新処理
	ObjectManager::GetInstance()->Update();

	if(tkl::Input::IsKeyDownTrigger(tkl::eKeys::KB_P)){
		mSceneManager->CallScene<PauseScene>();
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
	tkl::Font::DrawStringEx(0, 0, "ゲーム画面");

	// フィールドの更新
	mField->Draw(mParam);

	// オブジェクトの描画処理
	ObjectManager::GetInstance()->Draw();
}