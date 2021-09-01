#pragma once

#include "GameC.h"
#include <vector>

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

	static std::vector<std::vector<int>> colVec;
	
	static void update();
	static void init();
	static void draw();
	static void write();
	

private:
	
};