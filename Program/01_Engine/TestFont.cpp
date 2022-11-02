#include "TestFont.h"

#include "Mesh.h"
#include "FontManager.h"
#include "Camera/Camera.h"
#include "../02_Library/Utility.h"

namespace tkl
{
// TODO：一部の文字がうまく表示できない問題あり(未完成)
void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	tkl::FontManager* manager = tkl::FontManager::GetInstance();
	std::shared_ptr<Mesh> mesh = Mesh::CreatePlaneForTexture();

	float prevPosX = 0.0f;
	tkl::FontManager::Font prevFont = { nullptr, 0, 0 }, currentFont = { nullptr, 0, 0 };
	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = manager->GetFontTexture(buff[i]);
		float prevFontX = static_cast<float>(prevFont.strWidth * 0.5f);
		float currentFontX = static_cast<float>(currentFont.strWidth * 0.5f);

		// 新しい文字の位置
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){
			strPosX += prevPosX + prevFontX + currentFontX;
		}

		// スクリーン座標に変換
		float screenPosX = strPosX / static_cast<float>(camera->GetScreenWidth() * 0.5f);
		float screenPoxY = strPosY / static_cast<float>(camera->GetScreenHeight() * 0.5f);

		// テクスチャ用メッシュに情報を設定
		mesh->SetTexture(currentFont.texture);
		mesh->SetPosition(tkl::Vector3(screenPosX, screenPoxY, 0.0f));
		mesh->SetScale(tkl::Vector3(currentFont.strWidth, currentFont.strHeight, 1.0f));
		mesh->Draw(camera);

		// 次の文字位置計算用
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

} // namespace tkl