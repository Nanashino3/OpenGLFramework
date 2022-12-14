#include "PlayScene.h"

#include "../Field.h"
#include "../GameObject/AdvanceUnit.h"
#include "../GameObject/GameParameter.h"
#include "../GameObject/ObjectManager.h"
#include "../NotifyService/Notifier.h"
#include "../NotifyService/AdvanceUnitObserver.h"
#include "../NotifyService/DefenseUnitObserver.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/FixedCamera.h"
#include "../../01_Engine/Font.h"

const int CREATE_MAX = 5;

PlayScene::PlayScene()
: mCamera(nullptr)
, mElapsed(0)
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

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	tkl::Font::DrawStringEx(0, 0, "プレイシーン");

	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	// カメラ更新
	mCamera->Update();
	mParam->SetCamera(mCamera);
	mParam->SetDeltaTime(deltaTime);

	// TODO：暫定で耐久を設ける
	if(mEndurance != 0){
		// フィールドの更新
		mField->Update(mParam);

//	//******************************************************************
//	// TODO：最短経路表示用(デバッグとして呼び出したい)
//	for(int i = 0; i < mRoute.size(); ++i){
//		std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(SIZE);
//
//		float posX = mFirstPosX + SIZE * mRoute[i].column;
//		float posZ = mFirstPosZ + SIZE * mRoute[i].row;
//		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
//		mesh->SetPosition(tkl::Vector3(posX, 0, posZ));
//		mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
//		mesh->Draw(mCamera);
//	}
	
		tkl::Font::DrawStringEx(0, 100, "耐久値：%d", mEndurance);
		if(mParam->GetIsArrival()){
			if(mEndurance != 0) mEndurance -= 1;
			mParam->SetIsArrival(false);
		}

		// 進軍ユニット
		mElapsed += deltaTime;
		tkl::Font::DrawStringEx(0, 50, "DeltaTime：%f", deltaTime);

		if (mElapsed > 5.0f){
			mElapsed = 0;

			auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
			if(list->size() != CREATE_MAX){
				// 進軍ユニット生成
				ObjectManager::GetInstance()->Create<AdvanceUnit>(mParam);
			}
		}

		// オブジェクトの衝突判定
		ObjectManager::GetInstance()->Collision();

		// オブジェクトの更新処理
		ObjectManager::GetInstance()->Update(mParam);
	}

	// フィールドの更新
	mField->Draw(mParam);

	// オブジェクトの描画処理
	ObjectManager::GetInstance()->Draw(mParam);

	return nextScene;
}