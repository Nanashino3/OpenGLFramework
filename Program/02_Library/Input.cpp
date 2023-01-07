//***************************************************
// ファイル名：Input(入力クラス)
// 作　成　日：2022/10/6
#include "Input.h"
#include <string>

namespace tkl
{
GLFWwindow* Input::sWindow = nullptr;
double Input::sMouseScrollValue = 0.0f;

int Input::sKeyDown[GLFW_KEY_LAST] = {0};
int Input::sKeyXorDown[GLFW_KEY_LAST] = {0};
int Input::sKeyTrgDown[GLFW_KEY_LAST] = {0};
int Input::sKeyXorRelease[GLFW_KEY_LAST] = {0};
int Input::sKeyTrgRelease[GLFW_KEY_LAST] = {0};
int Input::sKeys[static_cast<int>(eKeys::KB_MAX)] = 
{
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

int Input::sMouseDown[GLFW_MOUSE_BUTTON_LAST] = {0};
int Input::sMouseXorDown[GLFW_MOUSE_BUTTON_LAST] = {0};
int Input::sMouseTrgDown[GLFW_MOUSE_BUTTON_LAST] = {0};
int Input::sMouseXorRelease[GLFW_MOUSE_BUTTON_LAST] = {0};
int Input::sMouseTrgRelease[GLFW_MOUSE_BUTTON_LAST] = {0};
int Input::sMouses[static_cast<int>(Input::eMouse::MOUSE_MAX)] =
{
	GLFW_MOUSE_BUTTON_LEFT,
	GLFW_MOUSE_BUTTON_RIGHT,
	GLFW_MOUSE_BUTTON_MIDDLE
};

// 入力システムの初期化
void Input::Initialize(GLFWwindow* const window, int screenWidth, int screenHeight)
{
	sWindow = window;
	glfwSetScrollCallback(window, CallbackMouseScroll);
}

// 入力システムの更新
void Input::Update()
{
	// キー入力状態更新
	memset(sKeyTrgDown, 0, sizeof(sKeyTrgDown));
	memset(sKeyTrgRelease, 0, sizeof(sKeyTrgRelease));
	for(uint32_t i = 0; i < static_cast<uint32_t>(eKeys::KB_MAX); ++i){
		sKeyDown[sKeys[i]] = glfwGetKey(sWindow, sKeys[i]);

		if(GLFW_PRESS == sKeyDown[sKeys[i]]){
			sKeyTrgDown[sKeys[i]] = (sKeyXorDown[sKeys[i]] ^ 0x01);
			sKeyXorDown[sKeys[i]] = 0x01;

			sKeyXorRelease[sKeys[i]] = 0;
		}else{
			sKeyXorDown[sKeys[i]] = 0;

			sKeyTrgRelease[sKeys[i]] = (sKeyXorRelease[sKeys[i]] ^ 0x01);
			sKeyXorRelease[sKeys[i]] = 0x01;
		}
	}

	// マウス入力状態更新
	memset(sMouseTrgDown, 0, sizeof(sMouseTrgDown));
	memset(sMouseTrgRelease, 0, sizeof(sMouseTrgRelease));
	for(uint32_t i = 0; i < static_cast<uint32_t>(eMouse::MOUSE_MAX); ++i){
		sMouseDown[sMouses[i]] = glfwGetMouseButton(sWindow, sMouses[i]);

		if(GLFW_PRESS == sMouseDown[sMouses[i]]){
			sMouseTrgDown[sMouses[i]] = (sMouseXorDown[sMouses[i]] ^ 0x01);
			sMouseXorDown[sMouses[i]] = 0x01;

			sMouseXorRelease[sMouses[i]] = 0;
		}else{
			sMouseXorDown[sMouses[i]] = 0;

			sMouseTrgRelease[sMouses[i]] = (sMouseXorRelease[sMouses[i]] ^ 0x01);
			sMouseXorRelease[sMouses[i]] = 0x01;
		}
	}
}

// マウス座標取得
void Input::GetMousePoint(int* posX, int* posY)
{
	double currentPosX = 0.0f, currentPosY = 0.0f;
	glfwGetCursorPos(sWindow, &currentPosX, &currentPosY);

	*posX = static_cast<int>(currentPosX);
	*posY = static_cast<int>(currentPosY);
}

// マウススクロール(コールバック関数)
void Input::CallbackMouseScroll(GLFWwindow* window, double x, double y)
{
	sMouseScrollValue = y;
}

} // namespace tkl