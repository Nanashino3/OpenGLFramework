#include "TestFont.h"

#include "Mesh.h"
#include "FontManager.h"
#include "../02_Library/Utility.h"

namespace tkl
{
void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	FontManager* manager = FontManager::GetInstance();
	std::shared_ptr<Mesh> mesh = Mesh::CreatePlaneForTexture();
	for(int i = 0; i < wcslen(buff); ++i){
//		std::shared_ptr<Texture> texture = manager->GetFontTexture(buff[i]);
		FontManager::Font font = manager->GetFontTexture(buff[i]);

		mesh->SetTexture(font.texture);
		mesh->SetPosition(tkl::Vector3(0.0f + 0.1f * i, 0.0f, 0.0f));
		mesh->Draw(camera);
	}
}

} // namespace tkl