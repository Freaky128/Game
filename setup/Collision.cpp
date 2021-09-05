#include "Collision.h"

// TODO [Matthew] lots of magic number 4's. need to be replaced with mapscale

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
	length = (Fpoint.x - Spoint.x) + 4; // magic number mapscale
	
	if (direction == 'd')
	{
		if (
			rec.x + rec.w > Spoint.x &&
			Spoint.x + length > rec.x &&
			rec.y + rec.h > Spoint.y &&
			Spoint.y + length > rec.y)
		{
			for (index = 0; index < (length / 4); index++)
			{
				if (
					rec.x + rec.w > Spoint.x + (index * 4) &&
					(Spoint.x + (index * 4)) + 3 > rec.x &&
					rec.y + rec.h > Spoint.y + (index * 4) &&
					(Spoint.y + (index * 4)) + 3 > rec.y)
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
			rec.y + rec.h > Spoint.y - (length - 4) &&
			Spoint.y + 4 > rec.y)
		{
			for (index = 0; index < (length / 4); index++)
			{
				if (
					rec.x + rec.w > Spoint.x + (index * 4) &&
					(Spoint.x + (index * 4)) + 3 > rec.x &&
					rec.y + rec.h > Spoint.y - (index * 4) &&
					(Spoint.y - (index * 4)) + 3 > rec.y)
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