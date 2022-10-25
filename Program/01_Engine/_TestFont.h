#pragma once

#include <string>
namespace tkl
{
	void DrawString(float posX, float posY, std::string str);
	class Texture* CreateFromFile(const char* fileName);

} // nemspace tkl