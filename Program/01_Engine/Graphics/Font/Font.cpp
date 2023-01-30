//****************************************************************************
// ファイル名：Font(フォントクラス)
// 作　成　日：2022/10/22
#include "Font.h"

#include <stdarg.h>
#include "FontManager.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/Texture.h"

#include "../../System.h"
#include "../../Camera/ScreenCamera.h"
#include "../../../02_Library/Utility.h"

namespace tkl
{
std::shared_ptr<Camera> Font::sCamera = nullptr;

//****************************************************************************
// 関数名：DrawStringEx
// 概　要：文字列描画
// 引　数：arg1 表示位置X
//       ：arg2 表示位置Y
//       ：arg3 カラー
//       ：arg4 文字列
//       ：arg5 パラメータ
// 戻り値：なし
// 詳　細：文字列を表示する
//****************************************************************************
void Font::DrawStringEx(float x, float y, const tkl::Vector3& color, const char* str, ...)
{
	char buff[1024] = {0};
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	sCamera->Update();

	DrawString(x, y, buff, sCamera, color);
}

//****************************************************************************
// 関数名：DrawString(private)
// 概　要：文字列描画
// 引　数：arg1 表示位置X
//       ：arg2 表示位置Y
//       ：arg3 文字列
//       ：arg4 カメラ
//       ：arg5 カラー
// 戻り値：なし
// 詳　細：指定位置に指定したカメラを使用して文字列を描画する
//****************************************************************************
void Font::DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera, const tkl::Vector3& color)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	float prevPosX = 0.0f;
	tkl::Character prevFont, currentFont;

	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = tkl::FontManager::GetInstance()->GetFontFromCreate(buff[i]);
		std::shared_ptr<Texture> texture = currentFont.texture;
		if(texture == nullptr){ return; }
		texture->SetColor(color);

		float prevFontX = static_cast<float>(prevFont.bearing.mX * 0.5f);
		float currentFontX = static_cast<float>(currentFont.bearing.mX * 0.5f);

		// 新しい文字の位置
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){ strPosX = prevPosX + prevFontX + currentFontX; }

		// スクリーン座標に変換(左上原点にする)
		float screenPosX = (strPosX + (texture->GetWidth() >> 1)) - static_cast<float>(camera->GetScreenWidth() >> 1);
		float screenPosY = static_cast<float>(camera->GetScreenHeight() >> 1) - (strPosY + (texture->GetHeight() >> 1));

		// テクスチャ用メッシュに情報を設定
		std::shared_ptr<Mesh> mesh = Mesh::CreateMeshForFont();
		mesh->SetTexture(texture);
		mesh->SetPosition(tkl::Vector3(screenPosX, screenPosY, 0.0f));
		mesh->Draw(camera);

		// 次の文字位置計算用
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

//****************************************************************************
// 関数名：DrawFontEx
// 概　要：フォント描画
// 引　数：arg1 表示位置X
//       ：arg2 表示位置Y
//       ：arg3 カラー
//       ：arg4 文字列
//       ：arg5 パラメータ
// 戻り値：なし
// 詳　細：読み込んでいるフォントで文字列を出力する
//****************************************************************************
void Font::DrawFontEx(float x, float y, int fontSize, const tkl::Vector3& color, const char* str, ...)
{
	char buff[1024] = { 0 };
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	sCamera->Update();

	DrawFont(x, y, buff, sCamera, fontSize, color);
}

//****************************************************************************
// 関数名：DrawFont(private)
// 概　要：文字列描画
// 引　数：arg1 表示位置X
//       ：arg2 表示位置Y
//       ：arg3 文字列
//       ：arg4 カメラ
//       ：arg5 カラー
// 戻り値：なし
// 詳　細：指定位置に指定したカメラを使用して文字列を描画する
//****************************************************************************
void Font::DrawFont(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera, int fontSize, const tkl::Vector3& color)
{
	// 文字毎に必要な情報を作成する
	float strOffsetX = 0.0f, strOffsetY = 0.0f;
	std::vector<std::shared_ptr<Mesh>> meshList;
	for(int i = 0; i < str.length(); ++i){
		Character ch = FontManager::GetInstance()->GetFontFromTTF(str[i], fontSize);

		if(ch.texture == nullptr){ return; }

		float strPosX = posX, strPosY = posY;
		if (i > 0) {
			strPosX += ch.bearing.mX;
			strPosY -= ch.texture->GetHeight() - ch.bearing.mY;
		}

		float screenPosX = strPosX + static_cast<float>(ch.texture->GetWidth() >> 1);
		float screenPosY = strPosY + static_cast<float>(ch.texture->GetHeight() >> 1);

		std::shared_ptr<Mesh> mesh = Mesh::CreateMeshForFont();
		ch.texture->SetColor(color);
		mesh->SetTexture(ch.texture);
		mesh->SetPosition(tkl::Vector3(screenPosX, screenPosY, 0.0f));
		meshList.emplace_back(mesh);

		posX += static_cast<float>(static_cast<int>(ch.advance.mX) >> 6);
		posY += static_cast<float>(static_cast<int>(ch.advance.mY) >> 6);

		strOffsetX = std::max(strOffsetX, screenPosX);
		strOffsetY = std::max(strOffsetY, screenPosY);
	}

	// 最後の文字の位置が文字列の最終なので
	// 各文字にオフセットを掛けて真ん中描画にする
	for(auto mesh : meshList){
		Vector3 pos = mesh->GetPosition();
		pos.mX -= strOffsetX * 0.5f;
		pos.mY -= strOffsetY * 0.5f;
		mesh->SetPosition(pos);

		mesh->Draw(sCamera);
	}
}

} // namespace tkl