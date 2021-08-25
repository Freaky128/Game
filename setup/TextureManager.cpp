#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	SDL_Surface* tempSurface = IMG_Load(filename);
	if (tempSurface == NULL) {
		printf("Could not find sprite file...\n");
	}
		SDL_Texture* tex = SDL_CreateTextureFromSurface(GameC::renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	
	
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(GameC::renderer, tex, &src, &dest, NULL, NULL, flip);
}
