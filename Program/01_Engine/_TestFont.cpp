#include "TestFont.h"

#include "FontManager.h"
#include "TextureManager.h"
#include "../02_Library/Utility.h"

namespace tkl
{
void DrawString(float posX, float posY, std::string str)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	FontManager* manager = FontManager::GetInstance();
	for(int i = 0; i < wcslen(buff); ++i){
		if(!manager->IsCreateFont(buff[i])){
			manager->CreateFontTexture(posX, posY, buff[i]);
		}
		manager->Draw(buff[i]);
	}
}

Texture* CreateFromFile(const char* fileName)
{
	TextureManager* manager = TextureManager::GetInstance();
	return manager->GetTexture(fileName);
}

} // namespace tkl