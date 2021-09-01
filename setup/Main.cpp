#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include "GameC.h"
#include "LvlColliderEditor.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 576

int main(int argc, char* args[]) {
	GameC gc;

	gc.init("Pokemon Like Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

	while (gc.running()) {
		
		gc.events();
		gc.update();
		gc.render();
		 
	}

	LvlColliderEditor::write();

	gc.clean();

	_CrtDumpMemoryLeaks();

	return 0;
}