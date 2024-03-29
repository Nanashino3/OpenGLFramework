//****************************************************************************
// ファイル名：UiHitPoint(ヒットポイントUIクラス)
// 作　成　日：2023/01/30
#include "UiHitPoint.h"

#include "../../../00_Game/GameObject/Parameter.h"
#include "../../../00_Game/GameObject/AdvanceUnit.h"

#include "../../../01_Engine/System.h"
#include "../../../01_Engine/ResourceManager.h"
#include "../../../01_Engine/Camera/ScreenCamera.h"
#include "../../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../../01_Engine/Graphics/Geometry/Texture.h"

static constexpr const char* BG_UI_FILE = "Resource/texture/ui/image_1.png";
static constexpr const char* UI_FILE = "Resource/texture/ui/image_2.png";

UiHitPoint::UiHitPoint(std::shared_ptr<Parameter> param)
: mScreenW(0), mScreenH(0)
, mMaxHitPoint(0.0f)
, mRectW(0.0f)
, mObject(nullptr)
, mParam(param)
, mTexture(nullptr)
, mBackGroundTexture(nullptr)
, m2DCam(nullptr)
{}

UiHitPoint::~UiHitPoint()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化
// 引　数：なし
// 戻り値：なし
// 詳　細：初期化処理を行う
//****************************************************************************
void UiHitPoint::Initialize(std::shared_ptr<AdvanceUnit> object)
{
	mObject = object;
	mMaxHitPoint = mObject->GetHitPoint();

	// ウィンドウサイズを取得し2D用カメラ生成
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(mScreenW, mScreenH);

	// ヒットポイントのテクスチャ生成
	mTexture = tkl::Mesh::CreateMeshForSprite();
	mTexture->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(UI_FILE));
	mRectW = (mTexture->GetTexture()->GetWidth()) * 0.5f;

	// ヒットポイントの背景テクスチャ生成
	mBackGroundTexture = tkl::Mesh::CreateMeshForSprite();
	mBackGroundTexture->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(BG_UI_FILE));
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 デルタタイム
// 戻り値：なし
// 詳　細：更新処理を行う
//****************************************************************************
void UiHitPoint::Update()
{
	m2DCam->Update();

	// ワールド座標→スクリーン座標へ変換
	tkl::Vector3 unitPos = mObject->GetPosition();
	tkl::Vector3 screenPos 
		= tkl::Vector3::ConvertWorldPosToScreenPos(mScreenW, mScreenH, unitPos, mParam->GetCamera()->GetView(), mParam->GetCamera()->GetProjection());
	
	// ヒットポイントUIの背景
	tkl::Vector3 bgPos = tkl::Vector3(screenPos.mX, screenPos.mY + 30.0f, 0.0f);
	mBackGroundTexture->SetPosition(bgPos);

	// ヒットポイントUI
	tkl::Vector3 uiPos = tkl::Vector3(screenPos.mX, screenPos.mY + 30.0f, 0.0f);
	float uiRatio = mObject->GetHitPoint() / mMaxHitPoint;
	uiPos.mX = screenPos.mX + (mRectW * uiRatio - mRectW);
	mTexture->SetPosition(uiPos);

	tkl::Vector3 uiScale = mTexture->GetScale();
	uiScale.mX = uiRatio;
	mTexture->SetScale(uiScale);

	// UIを表示する対象が生きているか
	if(!mObject->IsAlive()){ mIsEnabled = false; }
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：なし
// 戻り値：なし
// 詳　細：描画処理を行う
//****************************************************************************
void UiHitPoint::Draw()
{
	mBackGroundTexture->Draw(m2DCam);
	mTexture->Draw(m2DCam);
}