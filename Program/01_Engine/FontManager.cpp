#include "FontManager.h"

#include "Texture.h"
#include "../02_Library/FontTexture.h"

FontManager* FontManager::sMyInstance = nullptr;
FontManager::FontManager()
{}

FontManager::~FontManager()
{}

FontManager* FontManager::GetInstance()
{
	if(!sMyInstance){
		sMyInstance = new FontManager();
	}
	return sMyInstance;
}

void FontManager::DestroyInstance()
{
	delete sMyInstance;
}

// フォントによるテクスチャ作成
FontManager::Font FontManager::GetFontTexture(wchar_t once)
{
	auto iter = mCacheFonts.find(once);
	if(iter != mCacheFonts.end()){ return iter->second; }

	auto fontTex = tnl::CreateFontTexture(32, once);

	char* colorArray  = std::get<0>(fontTex).get();
	int textureWidth  = std::get<1>(fontTex);
	int textureHeight = std::get<2>(fontTex);
	int strWidth	  = std::get<3>(fontTex);
	int strHeight	  = std::get<4>(fontTex);

	std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureWidth, textureHeight, colorArray);
	Font font = {texture, strWidth, strHeight};
	mCacheFonts.emplace(once, font);

	return font;
}