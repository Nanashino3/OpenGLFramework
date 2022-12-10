#include "Font.h"

#include <stdarg.h>
#include "System.h"
#include "Mesh.h"
#include "Texture.h"
#include "FontManager.h"
#include "Camera/ScreenCamera.h"
#include "../02_Library/Utility.h"

namespace tkl
{
std::shared_ptr<Camera> Font::sCamera = nullptr;
std::shared_ptr<Mesh> Font::sMesh = nullptr;

void Font::DrawStringEx(float x, float y, const char* str, ...)
{
	char buff[255] = {0};
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	DrawString(x, y, buff, sCamera);
}

void Font::DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera)
{
	if(!sMesh){ sMesh = Mesh::CreatePlaneForTexture(); }

	camera->Update();

	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	float prevPosX = 0.0f;
	tkl::FontManager::Font prevFont = { nullptr, 0, 0 }, currentFont = { nullptr, 0, 0 };

	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = tkl::FontManager::GetInstance()->GetFontTexture(buff[i]);
		std::shared_ptr<Texture> texture = currentFont.texture;
		float prevFontX = static_cast<float>(prevFont.strWidth * 0.5f);
		float currentFontX = static_cast<float>(currentFont.strWidth * 0.5f);

		// 新しい文字の位置
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){ strPosX = prevPosX + prevFontX + currentFontX; }

		// スクリーン座標に変換(左上原点にする)
		float screenPosX = (strPosX + texture->GetTextureWidth() * 0.5f) / static_cast<float>(camera->GetScreenWidth() * 0.5f) - 1.0f;
		float screenPoxY = 1.0f - (strPosY + texture->GetTextureHeight() * 0.5f) / static_cast<float>(camera->GetScreenHeight() * 0.5f);

		// テクスチャ用メッシュに情報を設定
		sMesh->SetTexture(texture);
		sMesh->SetPosition(tkl::Vector3(screenPosX, screenPoxY, 0.0f));
		sMesh->SetScale(tkl::Vector3(texture->GetTextureWidth(), texture->GetTextureHeight(), 1.0f));
		sMesh->Draw(camera);

		// 次の文字位置計算用
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

} // namespace tkl