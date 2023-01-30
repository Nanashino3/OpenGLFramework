//****************************************************************************
// ファイル名：FontManager(フォント管理者クラス)
// 作　成　日：2022/10/27
#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include <memory>
#include <unordered_map>
#include "../../../02_Library/Vector.h"

namespace tkl
{
class Texture;
class FontManager
{
public:
	struct Character{
		std::shared_ptr<Texture> texture;
		Vector3 bearing;
		Vector3 advance;
	};

	static FontManager* GetInstance();
	static void DestroyInstance();

	Character GetFontFromCreate(wchar_t once);
	Character GetFontFromTTF(unsigned char ch, int fontSize = 32);

private:
	FontManager();
	~FontManager();

	FontManager(const FontManager& other){}
	FontManager& operator=(const FontManager& other){}

private:
	static FontManager* sMyInstance;
	std::unordered_map<wchar_t, Character> mCacheFonts;
};

using Character = tkl::FontManager::Character;

} // namespace tkl

#endif