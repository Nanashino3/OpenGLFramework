#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include <memory>
#include <unordered_map>

class Texture;
namespace tkl
{
class FontManager
{
public:
	struct Font{
		std::shared_ptr<Texture> texture;
		int strWidth;
		int strHeight;
	};

	static FontManager* GetInstance();
	static void DestroyInstance();

	Font GetFontTexture(wchar_t once);
private:
	FontManager();
	~FontManager();

	FontManager(const FontManager& other){}
	FontManager& operator=(const FontManager& other){}

private:
	static FontManager* sMyInstance;
	std::unordered_map<wchar_t, Font> mCacheFonts;
};

} // namespace tkl

#endif