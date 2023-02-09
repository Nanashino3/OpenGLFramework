//****************************************************************************
// ファイル名：UiHitPoint(ヒットポイントUIクラス)
// 作　成　日：2023/01/30
#include "UiHitPoint.h"

#include "../../../00_Game/GameObject/AdvanceUnit.h"

#include "../../../01_Engine/System.h"
#include "../../../01_Engine/ResourceManager.h"
#include "../../../01_Engine/Camera/ScreenCamera.h"
#include "../../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../../01_Engine/Graphics/Geometry/Texture.h"

static constexpr const char* UI_FILE = "Resource/texture/gauge_red.png";
static constexpr const char* BG_UI_FILE = "Resource/texture/gauge_whit.png";

#include "../../../01_Engine/Camera/FixedCamera.h"

// 矩形の幅、中心座標、割合
// 座標を返す
float Calc(float rectW, const tkl::Vector3& centerPos, float ratio)
{
	return centerPos.mX + (rectW * ratio - rectW);
}

UiHitPoint::UiHitPoint()
: mScreenW(0), mScreenH(0)
, mMaxHitPoint(0.0f)
, mRectW(0.0f)
, mTexture(nullptr)
, mBackGroundTexture(nullptr)
, mCamera(nullptr)
, mObject(nullptr)
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

	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);
	mCamera = std::make_shared<tkl::ScreenCamera>(mScreenW, mScreenH);

	mTexture = tkl::Mesh::CreateMeshForSprite();
	mTexture->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(UI_FILE));
	mRectW = (mTexture->GetTexture()->GetWidth()) * 0.5f;

	mBackGroundTexture = tkl::Mesh::CreateMeshForSprite();
	mBackGroundTexture->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(BG_UI_FILE));

	mTestCam = std::make_shared<tkl::FixedCamera>(mScreenW, mScreenH);
	mTestCam->SetPosition(tkl::Vector3(0.0f, 250.0f, 200.0f));
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
	mCamera->Update();
	mTestCam->Update();

	tkl::Vector3 unitPos = mObject->GetPosition();
	tkl::Vector3 screenPos 
		= tkl::Vector3::ConvertWorldPosToScreenPos(mScreenW, mScreenH, unitPos, mTestCam->GetView(), mTestCam->GetProjection());
	
	tkl::Vector3 bgPos = tkl::Vector3(screenPos.mX, screenPos.mY + 30.0f, 0.0f);
	mBackGroundTexture->SetPosition(bgPos);

	tkl::Vector3 uiPos = tkl::Vector3(screenPos.mX, screenPos.mY + 30.0f, 0.0f);
	float uiRatio = mObject->GetHitPoint() / mMaxHitPoint;
	uiPos.mX = Calc(mRectW, screenPos, uiRatio);
	mTexture->SetPosition(uiPos);

	tkl::Vector3 uiScale = mTexture->GetScale();
	uiScale.mX = uiRatio;
	mTexture->SetScale(uiScale);

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
	mBackGroundTexture->Draw(mCamera);
	mTexture->Draw(mCamera);
}