#define _CRTDBG_MAP_ALLOC // shit for dedugging memoery leaks
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include "GameC.h"
#include "LvlColliderEditor.h"
#include "PerfTimer.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 576

int main(int argc, char* args[]) {
	GameC gc;
	PerfTimer FPSperfTimer;

	Uint64 fTime = 0;
	Uint64 sTime = 0;
	long double ms = 0;
	int frames = 0;

	gc.init("Test Enviroment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false); // initilises SDL and window

	FPSperfTimer.start();
	
	while (gc.running()) { // main game loop
		
		gc.events();
		gc.update();
		gc.render();
		
		fTime = FPSperfTimer.getTicks();

		if (fTime - sTime >= 10000000)
		{
			printf("FPS: %d ", frames);
			sTime = fTime;
			frames = 0;
		}
		else
		{
			frames++;
		}
		
		//printf("instant FPS: %llu ", (10000000 / (fTime - sTime)));
		//ms = (fTime - sTime) / 10000.f;
		//printf("Time between frames %0.3Lf ", ms);
		
		//sTime = fTime;
	}

	LvlColliderEditor::writeRect(); // writes added colliders to .txt files
	LvlColliderEditor::writeTri();

	gc.clean(); // deallocates memory

	_CrtDumpMemoryLeaks(); // more shit for dedugging memoery leaks

	return 0;
}