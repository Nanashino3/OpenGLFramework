#include "FontManager.h"

#include "Texture.h"
#include "SpriteRenderer.h"
#include "../02_Library/Matrix.h"
#include "../02_Library/Utility.h"
#include "../02_Library/FontTexture.h"

FontManager* FontManager::sMyInstance = nullptr;
FontManager::FontManager()
{
	mRenderer = new SpriteRenderer("Sprite");
}

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

// ���Ƀt�H���g�쐬���݂�
bool FontManager::IsCreateFont(wchar_t once)
{
	auto iter = mCacheTexture.find(once);
	return iter != mCacheTexture.end();
}

// �t�H���g�e�N�X�`�����쐬
void FontManager::CreateFontTexture(wchar_t once)
{
	auto texture = tnl::CreateFontTexture(32, once);
	
	char* colorArray  = std::get<0>(texture).get();
	int textureWidth  = std::get<1>(texture);
	int textureHeight = std::get<2>(texture);

	mTexture = new Texture(textureWidth, textureHeight, colorArray);
	mCacheTexture.emplace(once, mTexture);
}

// �`��
void FontManager::Draw(wchar_t once)
{
	auto iter = mCacheTexture.find(once);
	if(iter != mCacheTexture.end()){ mRenderer->Draw(iter->second); }
}