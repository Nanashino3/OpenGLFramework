#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

class System
{
public:

	bool Initialize(int screenWidth, int screenHeight);
	bool ProcessMessage();
	void SwapBuffers();
	void Finalize();

private:
	GLFWwindow* mWindow;
};