#pragma once
#include "gameC.h"
class gameObject // not sure why I still keep these files they have been obsolete for ages now
{
public:
	gameObject(const char* spritesheet, int x, int y, int srcRectW, int srcRectH);
	~gameObject();

	void Update();
	void Render();
private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

