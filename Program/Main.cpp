#include <chrono>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include <iostream>
#include "00_Game/GameMain.h"
#include "01_Engine/System.h"

static std::chrono::system_clock::time_point clock_start, clock_end;
static std::chrono::system_clock::time_point fps_clock_start, fps_clock_end;

int main()
{
	tkl::System* system = tkl::System::GetInstance();
	if(!system->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT)){ exit(1); }

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	while(!system->ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		clock_end = std::chrono::system_clock::now();
		double micro_seconds = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(clock_end - clock_start).count());
		float deltaTime = static_cast<float>(micro_seconds / 1000.0 / 1000.0);
		clock_start = clock_end;

		fps_clock_start = std::chrono::system_clock::now();

		GameMain(deltaTime);

		system->SwapBuffers();

		// フレームレートコントロール
		fps_clock_end = std::chrono::system_clock::now();
		
		double fps_mic = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(fps_clock_end - fps_clock_start).count());
		float fps_mils = static_cast<float>(fps_mic / 1000.0);
		float fps_lim = 1000.0f / 60.0f;
		
		if (fps_lim > fps_mils) {
			timeBeginPeriod(1);
			Sleep(DWORD(fps_lim - fps_mils));
			timeEndPeriod(1);
		}
	}

	GameEnd();
	system->Finalize();
	tkl::System::DestroyInstance();
	return 0;
}