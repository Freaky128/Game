#define _CRTDBG_MAP_ALLOC // shit for dedugging memory leaks
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include "GameC.h"
#include "LvlColliderEditor.h"
#include "PerfTimer.h"
#include "Timer.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 576

int main(int argc, char* args[]) {
	GameC gc;
	
	PerfTimer FPSperfTimer;
	Uint64 PsTime = 0;
	Uint64 startTime = 0;
	Uint64 finishTime = 0;
	int frames = 0;
	bool mFPScap = false;
	const int targetFPS = 60;
	const int targetDelay = SDL_GetPerformanceFrequency() / targetFPS;
	int diff;
	float divFeq;

	gc.init("Test Enviroment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false); // initilises SDL and window

	FPSperfTimer.start();
	
	while (gc.running()) { // main game loop
		
		gc.events();
		gc.update();
		gc.render();

		finishTime = FPSperfTimer.getTicks();
		
		//if (mFPScap) // busy waiting cycle method - very good FPS but uses more CPU
		//{
		//	while ((finishTime - startTime) < targetDelay)
		//	{
		//		finishTime = FPSperfTimer.getTicks();
		//	}
		//	startTime = finishTime;
		//}

		//if (mFPScap) // delay method - lower FPS but low CPU usage
		//{
		//	
		//	diff = targetDelay - (finishTime - startTime);
		//	divFeq = static_cast<float>(diff) / SDL_GetPerformanceFrequency();
		//	divFeq = divFeq * 1000.f;
		//	
		//	if (divFeq > 0) 
		//	{
		//		SDL_Delay(divFeq);
		//	}
		//	
		//	finishTime = FPSperfTimer.getTicks();
		//	startTime = finishTime;
		//}

		if (mFPScap) // hybrid delay cycle method - good FPS and medium CPU usage
		{

			diff = targetDelay - (finishTime - startTime);
			divFeq = static_cast<float>(diff) / SDL_GetPerformanceFrequency();
			divFeq = divFeq * 1000.f;
			
			if (divFeq > 0)
			{
				SDL_Delay(divFeq - 2);
			}

			finishTime = FPSperfTimer.getTicks();

			while ((finishTime - startTime) < targetDelay)
			{
				finishTime = FPSperfTimer.getTicks();
			}

			startTime = finishTime;
		}
		
		
		if (finishTime - PsTime >= SDL_GetPerformanceFrequency())
		{
			//printf("pFPS: %d ", Pframes);
			gc.getFPS(frames);

			if (frames > (targetFPS + 5))
			{
				mFPScap = true;
				startTime = finishTime;
			}
			PsTime = finishTime;
			frames = 0;
		}
		else
		{
			frames++;
		}

	}

	LvlColliderEditor::writeRect(); // writes added colliders to .txt files
	LvlColliderEditor::writeTri();

	gc.clean(); // deallocates memory

	_CrtDumpMemoryLeaks(); // more shit for dedugging memory leaks

	return 0;
}