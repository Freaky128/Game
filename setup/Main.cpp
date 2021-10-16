#define _CRTDBG_MAP_ALLOC // shit for dedugging memoery leaks
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include "GameC.h"
#include "LvlColliderEditor.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 576

int main(int argc, char* args[]) {
	GameC gc;

	gc.init("Test Enviroment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false); // initilises SDL and window

	while (gc.running()) { // main game loop
		
		gc.events();
		gc.update();
		gc.render();
		 
	}

	LvlColliderEditor::writeRect(); // writes added colliders to .txt files
	LvlColliderEditor::writeTri();

	gc.clean(); // deallocates memory

	_CrtDumpMemoryLeaks(); // more shit for dedugging memoery leaks

	return 0;
}