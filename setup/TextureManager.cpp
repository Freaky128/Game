#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	SDL_Surface* tempSurface = IMG_Load(filename);
	if (tempSurface == NULL) {
		printf("Could not find sprite file...IMG_Error: %s\n", IMG_GetError);
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(GameC::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(GameC::renderer, tex, &src, &dest, NULL, NULL, flip);
}

SDL_Texture* TextureManager::LoadFontTexture(TTF_Font* font, const char* labelText, SDL_Color colour)
{
	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, labelText, colour); // should also maybe make a solid version.
	if (tempSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(GameC::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}