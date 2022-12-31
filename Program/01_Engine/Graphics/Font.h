//****************************************************************************
// ファイル名：Font(フォントクラス)
// 作　成　日：2022/10/22
#ifndef _FONT_H_
#define _FONT_H_

#include <string>
#include <memory>
#include "../../02_Library/Vector.h"

namespace tkl
{
class Mesh;
class Camera;
class Font
{
public:
	static void DrawStringEx(float x, float y, const tkl::Vector3& color, const char* str, ...);
	static void DrawFontEx(float x, float y, int fontSize, const tkl::Vector3& color, const char* str, ...);
private:
	Font(){}
	~Font(){}

	static void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<class Camera> camera, const tkl::Vector3& color = Vector3(1, 1, 1));
	static void DrawFont(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera, int fontSize = 32, const tkl::Vector3& color = Vector3(1, 1, 1));
private:
	static std::shared_ptr<Mesh> sMesh;
	static std::shared_ptr<Camera> sCamera;
};

} // namespace tkl

#endif