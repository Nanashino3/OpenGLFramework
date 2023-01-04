//****************************************************************************
// ファイル名：Canvas(キャンバスクラス)
// 作　成　日：2022/1/5
#include "Canvas.h"
#include "Button.h"

#include "../System.h"
#include "../../02_Library/Input.h"
#include "../../02_Library/Vector.h"

#include <iostream>

namespace tkl
{
Canvas::Canvas()
: mScreenW(0), mScreenH(0)
{
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);
}

Canvas::~Canvas()
{}

//****************************************************************************
// 関数名：AddButton
// 概　要：ボタン追加
// 引　数：arg1 ボタン名
//       ：arg2 表示位置
//       ：arg3 クリックした時の処理
// 戻り値：なし
// 詳　細：キャンバスにボタンを追加する
//****************************************************************************
void Canvas::AddButton(const std::string& name, const Vector3& pos, std::function<void()> onClick)
{
	std::shared_ptr<Button> btn = std::make_shared<Button>(name, pos, onClick);
	mButtons.emplace_back(btn);
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：キャンバスの更新処理をする
//****************************************************************************
void Canvas::Update()
{
	if(mButtons.empty()){ return; }

	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	mousePosX = mousePosX - (mScreenW >> 1);
	mousePosY = (mScreenH >> 1) - mousePosY;

	for(auto button : mButtons){
		button->SetIsFocus(false);
		if(button->ContainsPoint(tkl::Vector3(mousePosX, mousePosY, 0))){
			button->SetIsFocus(true);
		}

		button->Update();
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：arg1 カメラ
// 戻り値：なし
// 詳　細：キャンバスの描画処理をする
//****************************************************************************
void Canvas::Draw(std::shared_ptr<Camera> camera)
{
	for (auto button : mButtons) {
		button->Draw(camera);
	}
}

} // namespace tkl