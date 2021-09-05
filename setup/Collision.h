#pragma once

#include <SDL.h>
#include "ColliderComponent.h"

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AARL(const SDL_Rect& rec, const SDL_Point& Spoint, const SDL_Point& Fpoint, char direction);
};