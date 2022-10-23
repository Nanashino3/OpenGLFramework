#include "System.h"

#include <iostream>
#include "Input.h"

System::System()
: mWindow(nullptr)
{}

System::~System()
{}

bool System::Initialize(int screenWidth, int screenHeight)
{
	if(!glfwInit()){
		std::cerr << "Can't initialize GLFW." << std::endl;
		return false;
	}

	// OpenGL Version 4.6 Core Profile��I��
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

	// GLEW������������
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		std::cerr << "Can't initialize GLEW." << std::endl;
		return false;
	}

	// ���������̃^�C�~���O��҂�
	glfwSwapInterval(1);

	// �f�v�X�o�b�t�@(Z�o�b�t�@)��L���ɂ���
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	// ���̓f�o�C�X�̏�����
	tkl::Input::Initialize(mWindow, screenWidth, screenHeight);

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