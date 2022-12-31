//****************************************************************************
// ファイル名：FontManager(フォント管理者クラス)
// 作　成　日：2022/10/27
#include "FontManager.h"
#include "Geometry/Texture.h"

#include "../../01_Engine/ResourceManager.h"
#include "../../02_Library/FontTexture.h"
#include "../../02_Library/Utility.h"

namespace tkl
{
FontManager* FontManager::sMyInstance = nullptr;
FontManager::FontManager()
{}

FontManager::~FontManager()
{}

FontManager* FontManager::GetInstance()
{
	if(!sMyInstance){ sMyInstance = new FontManager; }
	return sMyInstance;
}

void FontManager::DestroyInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// 関数名：GetFontFromCreate
// 概　要：フォント取得(生成したフォント)
// 引　数：arg1 ワイド文字
// 戻り値：なし
// 詳　細：導入したライブラリで生成した文字を返す
//****************************************************************************
FontManager::Character FontManager::GetFontFromCreate(wchar_t once)
{
	auto iter = mCacheFonts.find(once);
	if(iter != mCacheFonts.end()){ return iter->second; }

	auto fontTex = tnl::CreateFontTexture(32, once);

	char* colorArray  = std::get<0>(fontTex).get();
	int textureWidth  = std::get<1>(fontTex);
	int textureHeight = std::get<2>(fontTex);
	int strWidth	  = std::get<3>(fontTex);
	int strHeight	  = std::get<4>(fontTex);

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->CreateBuffer(textureWidth, textureHeight, colorArray);

	Character ch = {texture, Vector3(strWidth, strHeight, 0)};
	mCacheFonts.emplace(once, ch);

	return ch;
}

//****************************************************************************
// 関数名：GetFontFromTTF
// 概　要：フォント取得(TTF)
// 引　数：arg1 ワイド文字
// 戻り値：なし
// 詳　細：TTFファイルから読み込んだフォントを取得
//****************************************************************************
FontManager::Character FontManager::GetFontFromTTF(unsigned char ch, int fontSize)
{
	auto font = tkl::ResourceManager::GetInstance()->GetFont(ch, fontSize);

	Character character = {
		std::get<0>(font), std::get<1>(font), std::get<2>(font)
	};
	return character;
}

} // namespace tkl