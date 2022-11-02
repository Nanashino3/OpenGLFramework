#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

namespace tkl
{
class System
{
public:
	System();
	~System();

	bool Initialize(int screenWidth, int screenHeight);
	bool ProcessMessage();
	void SwapBuffers();
	void Finalize();

private:
	GLFWwindow* mWindow;
};

} // namespace tkl

#endif