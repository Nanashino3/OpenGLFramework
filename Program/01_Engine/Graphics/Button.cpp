//****************************************************************************
// ファイル名：Button(ボタンクラス)
// 作　成　日：2022/1/5
#include "Button.h"

#include "../ResourceManager.h"
#include "../Intersect.h"
#include "../Graphics/Geometry/Mesh.h"
#include "../Graphics/Geometry/Texture.h"
#include "../Graphics/Font.h"
#include "../Sound/Sound.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Vector.h"

namespace tkl
{
Button::Button(const std::string& name, const Vector3& pos, std::function<void()> onClick)
: mIsFocus(false)
, mText(name)
, mMesh(nullptr)
, mButtonOn(nullptr)
, mButtonOff(nullptr)
, mOnClick(onClick)
{
	mSound = Sound::CreateSound("Resource/sound/decide.wav");

	mMesh = Mesh::CreateMeshForSprite();
	mMesh->SetPosition(pos);

	mButtonOn = ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/ButtonYellow.png");
	mButtonOff = ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/ButtonBlue.png");
}

Button::~Button()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：ボタンの更新処理をする
//****************************************************************************
void Button::Update()
{
	if(mIsFocus && Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)){
		if(mOnClick){
			mSound->Play();
			mOnClick();
		}
	}
	mMesh->SetTexture(mIsFocus ? mButtonOn : mButtonOff);
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：arg1 カメラ
// 戻り値：なし
// 詳　細：ボタンの描画処理をする
//****************************************************************************
void Button::Draw(std::shared_ptr<Camera> camera)
{
	mMesh->Draw(camera);
	Font::DrawFontEx(mMesh->GetPosition().mX, mMesh->GetPosition().mY - 5.0f, 32, Vector3(1, 1, 1), mText.c_str());
}

//****************************************************************************
// 関数名：ContainsPoint
// 概　要：ボタンの範囲内判定
// 引　数：arg1 マウス座標
// 戻り値：なし
// 詳　細：ボタン内にマウスポインタが入ったかを確認する
//****************************************************************************
bool Button::ContainsPoint(const Vector3& mousePos)
{
	Vector3 pos = mMesh->GetPosition();
	int textureW = mButtonOff->GetWidth();
	int textureH = mButtonOff->GetHeight();
	return tkl::IsIntersectPointRect(mousePos.mX, mousePos.mY, pos.mX, pos.mY, textureW, textureH);
}

} // namespace tkl