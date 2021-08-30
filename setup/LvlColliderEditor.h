#pragma once

#include "GameC.h"

class LvlColliderEditor
{
public:
	static bool mouseDown;
	static int ix;
	static int iy;

	static int fx;
	static int fy;

	static int x, y;

	static SDL_Rect destR, srcR;
	static SDL_Texture* tex;
	
	static void update();
	static void init();
	static void draw();
	

private:
	
};