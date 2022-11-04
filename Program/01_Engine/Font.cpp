#include "Font.h"

#include "System.h"
#include "Mesh.h"
#include "FontManager.h"
#include "Camera/FixedCamera.h"
#include "../02_Library/Utility.h"

namespace tkl
{
std::shared_ptr<Camera> Font::sCamera = nullptr;
std::shared_ptr<Mesh> Font::sMesh = nullptr;

Font::Font()
{}

Font::~Font()
{}

// TODO：一部の文字がうまく表示できない問題あり(未完成)
void Font::DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera)
{
	if(!sMesh){ sMesh = Mesh::CreatePlaneForTexture(); }
	if(!camera){
		int screenWidth = 0, screenHeight = 0;
		tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
		sCamera = std::make_shared<FixedCamera>(screenWidth, screenHeight);

		camera = sCamera;
	}

	camera->Update();

	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	float prevPosX = 0.0f;
	tkl::FontManager::Font prevFont = { nullptr, 0, 0 }, currentFont = { nullptr, 0, 0 };

	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = tkl::FontManager::GetInstance()->GetFontTexture(buff[i]);
		float prevFontX = static_cast<float>(prevFont.strWidth * 0.5f);
		float currentFontX = static_cast<float>(currentFont.strWidth * 0.5f);

		// 新しい文字の位置
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){ strPosX += prevPosX + prevFontX + currentFontX; }

		// スクリーン座標に変換
		float screenPosX = strPosX / static_cast<float>(camera->GetScreenWidth() * 0.5f);
		float screenPoxY = strPosY / static_cast<float>(camera->GetScreenHeight() * 0.5f);

		// テクスチャ用メッシュに情報を設定
		sMesh->SetTexture(currentFont.texture);
		sMesh->SetPosition(tkl::Vector3(screenPosX, screenPoxY, 0.0f));
		sMesh->Draw(camera);

		// 次の文字位置計算用
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

} // namespace tkl