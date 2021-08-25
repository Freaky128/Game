#include "gameObject.h"
#include "TextureManager.h"

gameObject::gameObject(const char* spritesheet, int x, int y, int srcRectW, int srcRectH) {

	objTexture = TextureManager::LoadTexture(spritesheet);

	xpos = x;
	ypos = y;
	
	srcRect.h = srcRectH;
	srcRect.w = srcRectW;
}

gameObject::~gameObject() {

}

void gameObject::Update() {

	xpos++;
	ypos++;

	
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 64;
	destRect.h = 64;
}

void gameObject::Render() {
	SDL_RenderCopy(GameC::renderer, objTexture, &srcRect, &destRect);
}