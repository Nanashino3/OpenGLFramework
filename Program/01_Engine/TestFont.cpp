#include "TestFont.h"

#include "FontManager.h"
#include "../02_Library/Utility.h"

namespace tkl
{
void DrawString(std::string str)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	FontManager* manager = FontManager::GetInstance();
	for(int i = 0; i < wcslen(buff); ++i){
		if(!manager->IsCreateFont(buff[i])){
			manager->CreateFontTexture(buff[i]);
		}
		manager->Draw(buff[i]);
	}
}

} // namespace tkl