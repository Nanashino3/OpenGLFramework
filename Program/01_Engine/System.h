#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <AL/alc.h>

static constexpr int WINDOW_WIDTH = 1024;
static constexpr int WINDOW_HEIGHT = 768;

namespace tkl
{
class System
{
public:
	static System* GetInstance();
	static void DestroyInstance();

	bool Initialize(int screenWidth, int screenHeight);
	bool ProcessMessage();
	void SwapBuffers();
	void GetWindowSize(int* screenWidth, int* screenHeight);
	void Finalize();

private:
	System();
	System(const System& other) {}
	System& operator=(const System& other) {}
	~System();

private:
	static System* sMyInstance;
	GLFWwindow* mWindow;
	ALCdevice* mALCDevice;
	ALCcontext* mALCContext;
};

} // namespace tkl

#endif