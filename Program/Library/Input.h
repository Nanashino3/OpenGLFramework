#pragma once
#include <GLFW/glfw3.h>

namespace tkl
{
class Input
{
public:
	// キーボード対応一覧
	enum class eKeys
	{
		KB_ENTER,	// エンター
		KB_LSHIFT,	// 左シフト
		KB_RSHIFT,	// 右シフト
		KB_SPACE,	// スペース
		KB_LEFT,	// 矢印(左)
		KB_UP,		// 矢印(上)
		KB_RIGHT,	// 矢印(右)
		KB_DOWN,	// 矢印(下)

		// アルファベット
		KB_A,
		KB_B,
		KB_C,
		KB_D,
		KB_E,
		KB_F,
		KB_G,
		KB_H,
		KB_I,
		KB_J,
		KB_K,
		KB_L,
		KB_M,
		KB_N,
		KB_O,
		KB_P,
		KB_Q,
		KB_R,
		KB_S,
		KB_T,
		KB_U,
		KB_V,
		KB_W,
		KB_X,
		KB_Y,
		KB_Z,

		// 数字
		KB_0,
		KB_1,
		KB_2,
		KB_3,
		KB_4,
		KB_5,
		KB_6,
		KB_7,
		KB_8,
		KB_9,

		KB_MAX
	};

	// マウス操作一覧
	enum class eMouse
	{
		MOUSE_INPUT_LEFT,
		MOUSE_INPUT_RIGHT,
		MOUSE_INPUT_CENTER,

		MAX_MOUSE_INPUT
	};

	static void Initialize(GLFWwindow* const window, int screenWidth, int screenHeight);
	static void Update(GLFWwindow* const window);

	// キーボード押しっぱなし検知(複数キー未対応)
	template<typename eKeys>
	static bool IsKeyDown(eKeys keys){
		return sKeyDownStatus[static_cast<int>(keys)];
	}

	// キーボード1フレーム押し検知(複数キー未対応)
	template<typename eKeys>
	static bool IsKeyDownTrigger(eKeys keys){
		return sKeyDownTrgStatus[static_cast<int>(keys)];
	}
 
	// マウス押しっぱなし検知(複数未対応)
	template<typename eMouse>
	static bool IsMouseInput(eMouse mouse) {
		return sMouseStatus[static_cast<int>(mouse)];
	}

	// マウス1フレーム押し検知(複数未対応)
	template<typename eMouse>
	static bool IsMouseInputTrigger(eMouse mouse){
		return sMouseTrgStatus[static_cast<int>(mouse)];
	}

	// マウス座標の取得
	static void GetMousePosition(int* posX, int* posY){
		*posX = sMousePosition[0], *posY = sMousePosition[1];
	}

	// マウススクロール量の取得
	static double GetMouseScrollValue(){ 
		double retVal = sMouseScrollValue;
		sMouseScrollValue = 0.0f;
		return retVal;
	}

private:
	Input(){}

	static void UpdateMousePos(GLFWwindow* const window);
	static void UpdateKeyboardStatus(GLFWwindow* const window);
	static void UpdateMouseScroll(GLFWwindow* window, double x, double y);
	static void UpdateMouseStatus(GLFWwindow* const window);

private:
	static int sWindowSize[2];													// ウィンドウサイズ
	
	// マウス関連変数
	static double sMousePosition[2];	// マウス座標
	static double sMouseScrollValue;	// マウススクロール量
	static bool sMouseStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];		// マウス状態
	static bool sPrevMouseStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];	// 前回のキー押下状態
	static bool sMouseTrgStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];	// キー押下トリガー状態
	static unsigned short sMouse[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];	// GLFWのマウス一覧

	// キーボード関連変数
	static bool sKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];			// キー押下状態
	static bool sPrevKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];		// 前回のキー押下状態
	static bool sKeyDownTrgStatus[static_cast<int>(Input::eKeys::KB_MAX)];		// キー押下トリガー状態
	static unsigned short sKeys[static_cast<int>(Input::eKeys::KB_MAX)];		// GLFWのキー一覧
};

} // namespace tkl

using eKeys = tkl::Input::eKeys;
using eMouse = tkl::Input::eMouse;