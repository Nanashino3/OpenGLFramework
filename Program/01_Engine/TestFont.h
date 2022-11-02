#pragma once

#include <string>
#include <memory>
namespace tkl
{
	void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<class Camera> camera = nullptr);
}