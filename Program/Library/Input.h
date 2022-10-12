#pragma once
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
		MOUSE_INPUT_LEFT,
		MOUSE_INPUT_RIGHT,
		MOUSE_INPUT_CENTER,

		MAX_MOUSE_INPUT
	};

	static void Initialize(GLFWwindow* const window, int screenWidth, int screenHeight);
	static void Update(GLFWwindow* const window);

	// �L�[�{�[�h�������ςȂ����m(�����L�[���Ή�)
	template<typename eKeys>
	static bool IsKeyDown(eKeys keys){
		return sKeyDownStatus[static_cast<int>(keys)];
	}

	// �L�[�{�[�h1�t���[���������m(�����L�[���Ή�)
	template<typename eKeys>
	static bool IsKeyDownTrigger(eKeys keys){
		return sKeyDownTrgStatus[static_cast<int>(keys)];
	}
 
	// �}�E�X�������ςȂ����m(�������Ή�)
	template<typename eMouse>
	static bool IsMouseInput(eMouse mouse) {
		return sMouseStatus[static_cast<int>(mouse)];
	}

	// �}�E�X1�t���[���������m(�������Ή�)
	template<typename eMouse>
	static bool IsMouseInputTrigger(eMouse mouse){
		return sMouseTrgStatus[static_cast<int>(mouse)];
	}

	// �}�E�X���W�̎擾
	static void GetMousePosition(int* posX, int* posY){
		*posX = sMousePosition[0], *posY = sMousePosition[1];
	}

	// �}�E�X�X�N���[���ʂ̎擾
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
	static int sWindowSize[2];													// �E�B���h�E�T�C�Y
	
	// �}�E�X�֘A�ϐ�
	static double sMousePosition[2];	// �}�E�X���W
	static double sMouseScrollValue;	// �}�E�X�X�N���[����
	static bool sMouseStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];		// �}�E�X���
	static bool sPrevMouseStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];	// �O��̃L�[�������
	static bool sMouseTrgStatus[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];	// �L�[�����g���K�[���
	static unsigned short sMouse[static_cast<int>(Input::eMouse::MAX_MOUSE_INPUT)];	// GLFW�̃}�E�X�ꗗ

	// �L�[�{�[�h�֘A�ϐ�
	static bool sKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];			// �L�[�������
	static bool sPrevKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];		// �O��̃L�[�������
	static bool sKeyDownTrgStatus[static_cast<int>(Input::eKeys::KB_MAX)];		// �L�[�����g���K�[���
	static unsigned short sKeys[static_cast<int>(Input::eKeys::KB_MAX)];		// GLFW�̃L�[�ꗗ
};

} // namespace tkl

using eKeys = tkl::Input::eKeys;
using eMouse = tkl::Input::eMouse;