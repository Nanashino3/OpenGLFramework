//***************************************************
// ファイル名：Input(入力クラス)
// 作　成　日：2022/10/6
#ifndef _INPUT_H_
#define _INPUT_H_

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
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_CENTER,

		MOUSE_MAX
	};

	// 入力システムの初期化
	static void Initialize(GLFWwindow* const window, int screenWidth, int screenHeight);
	// 入力システムの更新
	static void Update();
	// マウス座標取得
	static void GetMousePoint(int* posX, int* posY);

	// キー押下検知
	template <typename... tKeys>
	static bool IsKeyDown(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(auto elem : array){
			if(sKeyDown[sKeys[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// キー押下検知(1フレーム)
	template <typename... tKeys>
	static bool IsKeyDownTrigger(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(auto elem : array){
			if(sKeyTrgDown[sKeys[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// キー解放検知(1フレーム)
	template <typename... tKeys>
	static bool IsKeyReleaseTrigger(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(auto elem : array){
			if(sKeyTrgRelease[sKeys[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// マウス押下検知
	template <typename... tMouse>
	static bool IsMouseDown(tMouse... params){
		const eMouse array[] = { static_cast<eMouse>(params)... };
		for(auto elem : array){
			if(sMouseDown[sMouses[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// マウス押下検知(1フレーム)
	template <typename... tMouse>
	static bool IsMouseDownTrigger(tMouse... params){
		const eMouse array[] = { static_cast<eMouse>(params)... };
		for(auto elem : array){
			if(sMouseTrgDown[sMouses[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// マウス解放検知(1フレーム)
	template <typename... tMouse>
	static bool IsMouseReleaseTrigger(tMouse... params){
		const eMouse array[] = { static_cast<eMouse>(params)... };
		for(auto elem : array){
			if(sMouseTrgRelease[sMouses[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// マウススクロール量取得
	static float GetMouseScrollValue(){
		float retVal = static_cast<float>(sMouseScrollValue);
		sMouseScrollValue = 0.0f;
		return retVal;
	}

private:
	static void CallbackMouseScroll(GLFWwindow* window, double x, double y);

private:
	static GLFWwindow* sWindow;
	static double sMouseScrollValue;

	static int sKeyDown[GLFW_KEY_LAST];
	static int sKeyXorDown[GLFW_KEY_LAST];
	static int sKeyTrgDown[GLFW_KEY_LAST];
	static int sKeyXorRelease[GLFW_KEY_LAST];
	static int sKeyTrgRelease[GLFW_KEY_LAST];
	static int sKeys[static_cast<int>(Input::eKeys::KB_MAX)];

	static int sMouseDown[GLFW_MOUSE_BUTTON_LAST];
	static int sMouseXorDown[GLFW_MOUSE_BUTTON_LAST];
	static int sMouseTrgDown[GLFW_MOUSE_BUTTON_LAST];
	static int sMouseXorRelease[GLFW_MOUSE_BUTTON_LAST];
	static int sMouseTrgRelease[GLFW_MOUSE_BUTTON_LAST];
	static int sMouses[static_cast<int>(Input::eMouse::MOUSE_MAX)];
};

using eKeys = tkl::Input::eKeys;
using eMouse = tkl::Input::eMouse;

} // namespace tk

#endif