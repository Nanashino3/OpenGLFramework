#include "Input.h"

// デバッグ用
#include <iostream>

namespace tkl
{
int Input::sWindowSize[2] = {0};
int Input::sMousePosition[2] = {0};
double Input::sMouseScrollValue = 0.0;

bool Input::sPrevMouseStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)] = { false };
bool Input::sMouseTrgStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)] = { false };
bool Input::sMouseStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)] = { false };
unsigned short Input::sMouse[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)] = {
	GLFW_MOUSE_BUTTON_LEFT,
	GLFW_MOUSE_BUTTON_RIGHT,
	GLFW_MOUSE_BUTTON_MIDDLE
};

bool Input::sKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)] = { false };
bool Input::sPrevKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)] = { false };
bool Input::sKeyDownTrgStatus[static_cast<int>(Input::eKeys::KB_MAX)] = { false };
unsigned short Input::sKeys[static_cast<int>(Input::eKeys::KB_MAX)] = {
		GLFW_KEY_ENTER,			// エンター
		GLFW_KEY_LEFT_SHIFT,	// 左シフト
		GLFW_KEY_RIGHT_SHIFT,	// 右シフト
		GLFW_KEY_SPACE,			// スペース
		GLFW_KEY_LEFT,			// 矢印(左)
		GLFW_KEY_UP,			// 矢印(上)
		GLFW_KEY_RIGHT,			// 矢印(右)
		GLFW_KEY_DOWN,			// 矢印(下)

		// アルファベット
		GLFW_KEY_A,
		GLFW_KEY_B,
		GLFW_KEY_C,
		GLFW_KEY_D,
		GLFW_KEY_E,
		GLFW_KEY_F,
		GLFW_KEY_G,
		GLFW_KEY_H,
		GLFW_KEY_I,
		GLFW_KEY_J,
		GLFW_KEY_K,
		GLFW_KEY_L,
		GLFW_KEY_M,
		GLFW_KEY_N,
		GLFW_KEY_O,
		GLFW_KEY_P,
		GLFW_KEY_Q,
		GLFW_KEY_R,
		GLFW_KEY_S,
		GLFW_KEY_T,
		GLFW_KEY_U,
		GLFW_KEY_V,
		GLFW_KEY_W,
		GLFW_KEY_X,
		GLFW_KEY_Y,
		GLFW_KEY_Z,

		// 数字
		GLFW_KEY_0,
		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9
};

void Input::Initialize(GLFWwindow* const window, int screenWidth, int screenHeight)
{
	sWindowSize[0] = screenWidth;
	sWindowSize[1] = screenHeight;

	glfwSetCursorPosCallback(window, CallbackMousePos);
	glfwSetScrollCallback(window, CallbackMouseScroll);
}

void Input::Update(GLFWwindow* const window)
{
	UpdateKeyboardStatus(window);
	UpdateMouseStatus(window);
}

// キー入力入力状態
void Input::UpdateKeyboardStatus(GLFWwindow* const window)
{
	for(int i = 0; i < static_cast<int>(eKeys::KB_MAX); ++i){
		sKeyDownStatus[i] = glfwGetKey(window, sKeys[i]);

		sKeyDownTrgStatus[i] = false;
		if(sPrevKeyDownStatus[i] != sKeyDownStatus[i]){
			if(sKeyDownStatus[i] != GLFW_RELEASE){ sKeyDownTrgStatus[i] = true; }
		}
		sPrevKeyDownStatus[i] = sKeyDownStatus[i];
	}
}

// マウス入力状態更新
void Input::UpdateMouseStatus(GLFWwindow* const window)
{
	for(int i = 0; i < static_cast<int>(eMouse::MAX_MOUSE_INPUT); ++i){
		sMouseStatus[i] = glfwGetMouseButton(window, sMouse[i]);

		sMouseTrgStatus[i] = false;
		if(sPrevMouseStatus[i] != sMouseStatus[i]){
			if(sMouseStatus[i] != GLFW_RELEASE){ sMouseTrgStatus[i] = true; }
		}
		sPrevMouseStatus[i] = sMouseStatus[i];
	}
}

// マウススクロール更新(コールバック関数)
void Input::CallbackMouseScroll(GLFWwindow* window, double x, double y)
{
	sMouseScrollValue = y;
}

// マウス座標更新(コールバック関数)
void Input::CallbackMousePos(GLFWwindow* const window, double x, double y)
{
	// 現在座標
	sMousePosition[0] = static_cast<int>(x);
	sMousePosition[1] = static_cast<int>(y);
}

} // namespace tkl