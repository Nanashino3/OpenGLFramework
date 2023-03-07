#include "EffectBomb.h"

#include "../../../00_Game/GameObject/Parameter.h"
#include "../../../00_Game/GameObject/AdvanceUnit.h"

#include "../../../01_Engine/System.h"
#include "../../../01_Engine/Camera/ScreenCamera.h"
#include "../../../01_Engine/Graphics/Geometry/Sprite.h"

// ファイルパス
static constexpr const char* BOMB_EFFECT = "Resource/texture/bomb.png";

EffectBomb::EffectBomb(std::shared_ptr<Parameter> param)
: mParam(param)
{}

EffectBomb::~EffectBomb()
{}

void EffectBomb::Initialize(const tkl::Vector3& drawPosition)
{
	// スプライト生成
	mSprite = std::make_shared<tkl::Sprite>(BOMB_EFFECT, 16, 8, 2, true);

	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// ワールド座標→スクリーン座標へ変換
	tkl::Vector3 screenPos 
		= tkl::Vector3::ConvertWorldPosToScreenPos(screenW, screenH, drawPosition, mParam->GetCamera()->GetView(), mParam->GetCamera()->GetProjection());

	// 描画位置を設定
	mSprite->SetPosition(screenPos);
}

void EffectBomb::Update(float deltaTime)
{
	// 最終フレームまで描画したら削除可能
	if((mSprite->GetCurrentFrame() + 1) == mSprite->GetTotalFrames()){
		mIsEnabled = false;
		return;
	}
	m2DCam->Update();
	mSprite->Update(deltaTime);
}
	
void EffectBomb::Draw()
{
	mSprite->Draw(m2DCam);
}