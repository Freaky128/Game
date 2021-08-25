#pragma once
#include "gameC.h"
class gameObject
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

