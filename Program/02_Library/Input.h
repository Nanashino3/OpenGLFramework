//***************************************************
// �t�@�C�����FInput(���̓N���X)
// ��@���@���F2022/10/6
#ifndef _INPUT_H_
#define _INPUT_H_

#include <GLFW/glfw3.h>
namespace tkl
{
class Input
{
public:
	// �L�[�{�[�h�Ή��ꗗ
	enum class eKeys
	{
		KB_ENTER,	// �G���^�[
		KB_LSHIFT,	// ���V�t�g
		KB_RSHIFT,	// �E�V�t�g
		KB_SPACE,	// �X�y�[�X
		KB_LEFT,	// ���(��)
		KB_UP,		// ���(��)
		KB_RIGHT,	// ���(�E)
		KB_DOWN,	// ���(��)

		// �A���t�@�x�b�g
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

		// ����
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

	// �}�E�X����ꗗ
	enum class eMouse
	{
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_CENTER,

		MOUSE_MAX
	};

	// ���̓V�X�e���̏�����
	static void Initialize(GLFWwindow* const window, int screenWidth, int screenHeight);
	// ���̓V�X�e���̍X�V
	static void Update();
	// �}�E�X���W�擾
	static void GetMousePoint(int* posX, int* posY);

	// �L�[�������m
	template <typename... tKeys>
	static bool IsKeyDown(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(auto elem : array){
			if(sKeyDown[sKeys[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// �L�[�������m(1�t���[��)
	template <typename... tKeys>
	static bool IsKeyDownTrigger(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(auto elem : array){
			if(sKeyTrgDown[sKeys[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// �L�[������m(1�t���[��)
	template <typename... tKeys>
	static bool IsKeyReleaseTrigger(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(auto elem : array){
			if(sKeyTrgRelease[sKeys[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// �}�E�X�������m
	template <typename... tMouse>
	static bool IsMouseDown(tMouse... params){
		const eMouse array[] = { static_cast<eMouse>(params)... };
		for(auto elem : array){
			if(sMouseDown[sMouses[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// �}�E�X�������m(1�t���[��)
	template <typename... tMouse>
	static bool IsMouseDownTrigger(tMouse... params){
		const eMouse array[] = { static_cast<eMouse>(params)... };
		for(auto elem : array){
			if(sMouseTrgDown[sMouses[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// �}�E�X������m(1�t���[��)
	template <typename... tMouse>
	static bool IsMouseReleaseTrigger(tMouse... params){
		const eMouse array[] = { static_cast<eMouse>(params)... };
		for(auto elem : array){
			if(sMouseTrgRelease[sMouses[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	// �}�E�X�X�N���[���ʎ擾
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