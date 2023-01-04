//****************************************************************************
// ファイル名：Button(ボタンクラス)
// 作　成　日：2022/1/5
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <memory>
#include <string>
#include <functional>

namespace tkl
{
class Mesh;
class Texture;
class Camera;
class Vector3;
class Button
{
public:
	Button(const std::string& name, const Vector3& pos, std::function<void()> onClick);
	~Button();

	void Update();
	void Draw(std::shared_ptr<Camera> camera);

	bool ContainsPoint(const Vector3& mousePos);
	void SetIsFocus(bool value){ mIsFocus = value; }

private:
	bool mIsFocus;
	std::string mText;
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<Texture> mButtonOn;
	std::shared_ptr<Texture> mButtonOff;

	std::function<void()> mOnClick;
};

} // namespace tkl

#endif