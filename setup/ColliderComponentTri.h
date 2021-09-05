#pragma once

#include <string>
#include "Components.h"
#include "TextureManager.h"

class ColliderComponentTri : public Component
{
public:
	SDL_Texture* tex;
	SDL_Rect srcR, destR;
	
	char direction;

	SDL_Point IstartP, startP;
	SDL_Point IfinalP, finalP;
	
	int loop;
	int mapScale;
	int index;
	
	ColliderComponentTri(char dir, int Sxpos, int Sypos, int Fxpos, int Fypos, int scale)
	{
		direction = dir;
		IstartP.x = Sxpos;
		IstartP.y = Sypos;
		IfinalP.x = Fxpos;
		IfinalP.y = Fypos;
		mapScale = scale;

		loop = ((IfinalP.x - IstartP.x) / scale) + 1;
	}

	void init() override
	{
		tex = TextureManager::LoadTexture("assets/collider.png");
		srcR = { 0, 0, 32, 32 };
		destR.w = mapScale;
		destR.h = mapScale;
	}

	void update() override
	{
		startP.x = IstartP.x - GameC::camera.x;
		startP.y = IstartP.y - GameC::camera.y;
		finalP.x = IfinalP.x - GameC::camera.x;
		finalP.y = IfinalP.y - GameC::camera.y;
	}

	void draw() override
	{
		if (direction == 'd')
		{
			for (index = 0; index < loop; index ++)
			{
				destR.x = startP.x + (index * mapScale);
				destR.y = startP.y + (index * mapScale);
				TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
			}
		}
		else
		{
			for (index = 0; index < loop; index++)
			{
				destR.x = startP.x + (index * mapScale);
				destR.y = startP.y - (index * mapScale);
				TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
			}
		}
	}
};