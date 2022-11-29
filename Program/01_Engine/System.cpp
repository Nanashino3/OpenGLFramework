#include "System.h"

#include <iostream>
#include "../02_Library/Input.h"

namespace tkl
{
System* System::sMyInstance = nullptr;
System::System()
: mWindow(nullptr)
, mALCDevice(nullptr), mALCContext(nullptr)
{}

System::~System()
{
	// オーディオシステムの解除
	if (!alcMakeContextCurrent(nullptr))
		std::cerr << "Failed to make context to nullptr." << std::endl;

	alcDestroyContext(mALCContext);
	if (mALCContext) std::cerr << "Failed to unset during close." << std::endl;

	if (!alcCloseDevice(mALCDevice))
		std::cerr << "Failed to close device." << std::endl;
}

System* System::GetInstance()
{
	if(!sMyInstance){
		sMyInstance = new System();
	}
	return sMyInstance;
}
void System::DestroyInstance()
{
	delete sMyInstance;
}

bool System::Initialize(int screenWidth, int screenHeight)
{
	if(!glfwInit()){
		std::cerr << "Can't initialize GLFW." << std::endl;
		return false;
	}

	// OpenGL Version 4.6 Core Profileを選択
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(screenWidth, screenHeight, "GLFramwwork", NULL, NULL);
	if(!mWindow){
		std::cerr << "Can't create GLFW window." << std::endl;
		return false;
	}
	glfwMakeContextCurrent(mWindow);

	// GLEWを初期化する
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		std::cerr << "Can't initialize GLEW." << std::endl;
		return false;
	}

	// 入力デバイスの初期化
	tkl::Input::Initialize(mWindow, screenWidth, screenHeight);

	// オーディオシステムの初期化
	mALCDevice = alcOpenDevice(nullptr);
	if (!mALCDevice) std::cerr << "Failed to open device." << std::endl;

	mALCContext = alcCreateContext(mALCDevice, nullptr);
	if (!mALCContext) std::cerr << "Failed to create context." << std::endl;

	if (!alcMakeContextCurrent(mALCContext))
		std::cerr << "Failed to make context current." << std::endl;

	return true;
}

bool System::ProcessMessage()
{
	tkl::Input::Update();
	return glfwWindowShouldClose(mWindow);
}

void System::SwapBuffers()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void System::Finalize()
{
	glfwTerminate();
}

void System::GetWindowSize(int* screenWidth, int* screenHeight)
{
	glfwGetWindowSize(mWindow, screenWidth, screenHeight);
}

} // namespace tkl