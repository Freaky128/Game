#include "Collision.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w > recB.x &&
		recB.x + recB.w > recA.x &&
		recA.y + recA.h > recB.y &&
		recB.y + recB.h > recA.y) 
	{
		return true;
	}
	else {
		return false;
	}
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if(AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << "hit: " << colB.tag << std::endl;

		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::AARL(const SDL_Rect& rec, const SDL_Point& Spoint, const SDL_Point& Fpoint, char direction)
{
	int index;
	int length;
	length = (Fpoint.x - Spoint.x) + SCALE;
	
	if (direction == 'd')
	{
		if (
			rec.x + rec.w > Spoint.x &&
			Spoint.x + length > rec.x &&
			rec.y + rec.h > Spoint.y &&
			Spoint.y + length > rec.y)
		{
			for (index = 0; index < (length / SCALE); index++)
			{
				if (
					rec.x + rec.w > Spoint.x + (index * SCALE) &&
					(Spoint.x + (index * SCALE)) + 3 > rec.x &&
					rec.y + rec.h > Spoint.y + (index * SCALE) &&
					(Spoint.y + (index * SCALE)) + 3 > rec.y)
				{
					return true;
				}
			}
			return false;
		}
		else
		{
			return false;
		}

	}
	else
	{
		if ( // magic numbers mapscale
			rec.x + rec.w > Spoint.x &&
			Spoint.x + length > rec.x &&
			rec.y + rec.h > Spoint.y - (length - SCALE) &&
			Spoint.y + SCALE > rec.y)
		{
			for (index = 0; index < (length / SCALE); index++)
			{
				if (
					rec.x + rec.w > Spoint.x + (index * SCALE) &&
					(Spoint.x + (index * SCALE)) + 3 > rec.x &&
					rec.y + rec.h > Spoint.y - (index * SCALE) &&
					(Spoint.y - (index * SCALE)) + 3 > rec.y)
				{
					return true;
				}
			}
			return false;
		}
		else
		{
			return false;
		}
	}
}