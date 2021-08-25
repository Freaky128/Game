#pragma once

#include "ECS.h"
#include <SDL.h>


class MapComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	MapComponent() = default;

	~MapComponent()
	{
		SDL_DestroyTexture(texture);
	}

	MapComponent(const char* path, int xpos, int ypos, int width, int height, int scale)
	{
		texture = TextureManager::LoadTexture(path);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = 0; //magic numbers
		srcRect.y = 0;
		srcRect.w = width;
		srcRect.h = height;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = width * scale;
		destRect.h = height * scale;

	}

	void update() override
	{
		destRect.x = position.x - GameC::camera.x;
		destRect.y = position.y - GameC::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};