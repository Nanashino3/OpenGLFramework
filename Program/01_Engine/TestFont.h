#pragma once

#include <string>
#include <memory>
class Camera;
namespace tkl
{
void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera = nullptr);
}