//****************************************************************************
// �t�@�C�����FCanvas(�L�����o�X�N���X)
// ��@���@���F2022/1/5
#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <vector>
#include <string>
#include <functional>

namespace tkl
{
class Camera;
class Vector3;
class Button;
class Canvas
{
public:
	Canvas();
	~Canvas();

	void Update();
	void Draw(std::shared_ptr<Camera> camera);

	void AddButton(const std::string& name, const Vector3& pos, std::function<void()> onClick);

private:
	int mScreenW, mScreenH;
	std::vector<std::shared_ptr<Button>> mButtons;
};

} // namespace tkl

#endif