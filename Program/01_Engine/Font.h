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
	static void DrawStringEx(float x, float y, const char* str, ...);

private:
	Font(){}
	~Font(){}

	static void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<class Camera> camera);

private:
	static std::shared_ptr<Camera> sCamera;
	static std::shared_ptr<Mesh> sMesh;
};

} // namespace tkl

#endif