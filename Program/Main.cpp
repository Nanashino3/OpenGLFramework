#include <iostream>
#include "00_Game/GameMain.h"
#include "01_Engine/System.h"

int main()
{
	tkl::System* system = tkl::System::GetInstance();
	if(!system->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT)){ exit(1); }

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	float clockStart = glfwGetTime(), clockEnd = 0.0f;
	const float interval = 1.0f/60.0f;

	while(!system->ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ƒtƒŒ[ƒ€ŠÔ‚ÌŒo‰ßŠÔ
		clockEnd = static_cast<float>(glfwGetTime());
		float deltaTime = clockEnd - clockStart;
		if(deltaTime >= interval){ clockStart = clockEnd; }

		GameMain(deltaTime);

		system->SwapBuffers();
	}

	GameEnd();
	system->Finalize();
	tkl::System::DestroyInstance();
	return 0;
}