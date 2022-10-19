#include "Input.h"

// �f�o�b�O�p
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
		GLFW_KEY_ENTER,			// �G���^�[
		GLFW_KEY_LEFT_SHIFT,	// ���V�t�g
		GLFW_KEY_RIGHT_SHIFT,	// �E�V�t�g
		GLFW_KEY_SPACE,			// �X�y�[�X
		GLFW_KEY_LEFT,			// ���(��)
		GLFW_KEY_UP,			// ���(��)
		GLFW_KEY_RIGHT,			// ���(�E)
		GLFW_KEY_DOWN,			// ���(��)

		// �A���t�@�x�b�g
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

		// ����
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

// �L�[���͓��͏��
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

// �}�E�X���͏�ԍX�V
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

// �}�E�X�X�N���[���X�V(�R�[���o�b�N�֐�)
void Input::CallbackMouseScroll(GLFWwindow* window, double x, double y)
{
	sMouseScrollValue = y;
}

// �}�E�X���W�X�V(�R�[���o�b�N�֐�)
void Input::CallbackMousePos(GLFWwindow* const window, double x, double y)
{
	// ���ݍ��W
	sMousePosition[0] = static_cast<int>(x);
	sMousePosition[1] = static_cast<int>(y);
}

} // namespace tkl