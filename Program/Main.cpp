#include <iostream>
#include "Library/System.h"
#include "Game/GameMain.h"

int main()
{
	System system;
	if(!system.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT)){
		exit(1);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	float deltaTime = 0.0f;
	while(!system.ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameMain(deltaTime);

		system.SwapBuffers();
	}

	GameEnd();
	system.Finalize();
	return 0;
}