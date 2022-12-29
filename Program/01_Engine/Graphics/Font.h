//****************************************************************************
// ファイル名：Font(フォントクラス)
// 作　成　日：2022/10/22
#ifndef _FONT_H_
#define _FONT_H_

#include <string>
#include <memory>

namespace tkl
{
class Camera;
class Mesh;
class Font
{
public:
	static void DrawFontEx(float x, float y, float scale, const char* str, ...);
	static void DrawStringEx(float x, float y, const char* str, ...);

private:
	Font(){}
	~Font(){}

	static void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<class Camera> camera);

private:
	static std::shared_ptr<Mesh> sMesh;
	static std::shared_ptr<Camera> sCamera;
};

} // namespace tkl

#endif