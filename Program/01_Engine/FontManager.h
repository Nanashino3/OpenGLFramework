#pragma once
#include <unordered_map>

class Texture;
class SpriteRenderer;
class FontManager
{
public:
	static FontManager* GetInstance();
	static void DestroyInstance();

	bool IsCreateFont(wchar_t once);
	void CreateFontTexture(wchar_t once);
	void Draw(wchar_t once);

private:
	FontManager();
	~FontManager();

	FontManager(const FontManager& other) {}
	FontManager& operator=(const FontManager& other) {}

private:
	static FontManager* sMyInstance;

	Texture* mTexture;
	SpriteRenderer* mRenderer;
	std::unordered_map<wchar_t, Texture*> mCacheTexture;
};