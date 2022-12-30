//****************************************************************************
// ファイル名：Font(フォントクラス)
// 作　成　日：2022/10/22
#include "Font.h"

#include <stdarg.h>
#include "FontManager.h"
#include "Geometry/Mesh.h"
#include "Geometry/Texture.h"

#include "../System.h"
#include "../Camera/ScreenCamera.h"
#include "../../02_Library/Utility.h"

namespace tkl
{
std::shared_ptr<Mesh> Font::sMesh = nullptr;
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

	sMesh = Mesh::CreateMeshForFont();
	
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
		float prevFontX = static_cast<float>(prevFont.bearing.mX * 0.5f);
		float currentFontX = static_cast<float>(currentFont.bearing.mX * 0.5f);

		// 新しい文字の位置
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){ strPosX = prevPosX + prevFontX + currentFontX; }

		// スクリーン座標に変換(左上原点にする)
		float screenPosX = (strPosX + texture->GetWidth() * 0.5f) / static_cast<float>(camera->GetScreenWidth() * 0.5f) - 1.0f;
		float screenPoxY = 1.0f - (strPosY + texture->GetHeight() * 0.5f) / static_cast<float>(camera->GetScreenHeight() * 0.5f);

		// テクスチャ用メッシュに情報を設定
		texture->SetColor(color);
		sMesh->SetTexture(texture);
		sMesh->SetPosition(tkl::Vector3(screenPosX, screenPoxY, 0.0f));
		sMesh->Draw(camera);

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
void Font::DrawFontEx(float x, float y, const tkl::Vector3& color, const char* str, ...)
{
	char buff[1024] = { 0 };
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	sMesh = Mesh::CreateMeshForFont();

	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	sCamera->Update();

	DrawFont(x, y, buff, sCamera, color);
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
void Font::DrawFont(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera, const tkl::Vector3& color)
{
	for (int i = 0; i < str.length(); ++i) {
		tkl::Character ch = tkl::FontManager::GetInstance()->GetFontFromTTF(str[i]);

		if (ch.texture == nullptr) { return; }

		float strPosX = posX + ch.bearing.mX;
		float strPosY = posY - (ch.texture->GetHeight() - ch.bearing.mY);

		float screenPosX = (strPosX + (ch.texture->GetWidth() >> 1)) / static_cast<float>(sCamera->GetScreenWidth() >> 1);
		float screenPosY = (strPosY + (ch.texture->GetHeight() >> 1)) / static_cast<float>(sCamera->GetScreenHeight() >> 1);

		ch.texture->SetColor(color);
		sMesh->SetTexture(ch.texture);
		sMesh->SetPosition(tkl::Vector3(screenPosX, screenPosY, 0));
		sMesh->Draw(sCamera);

		posX += (static_cast<int>(ch.advance.mX) >> 6);
		posY += (static_cast<int>(ch.advance.mY) >> 6);
	}
}

} // namespace tkl