#include "AnimalBehaviour.h"

void AnimalBehaviour::update()
{
	animalPos = transform->position;
	destRect = sprite->destRect;

	destRect.x += GameC::camera.x;
	destRect.y += GameC::camera.y;

	//printf("c.x: %d, c.y: %d, c.w: %d, c.h: %d\n", GameC::camera.x, GameC::camera.y, GameC::camera.w, GameC::camera.h);
	//printf("bear c.x: %d, c.y: %d, c.w: %d, c.h: %d\n", destRect.x, destRect.y, destRect.w, destRect.h);
	
	if (Collision::AABB(destRect, GameC::camera))
	{
		printf("xpos: %f ypos: %f\n", animalPos.x, animalPos.y);
		
		Xdif = 320 - (static_cast<int>(animalPos.x) - GameC::camera.x + (destRect.w / 2));
		Ydif = 288 - (static_cast<int>(animalPos.y) - GameC::camera.y + (destRect.h / 2));
		printf("Xdif: %d Ydif: %d\n", Xdif, Ydif);

		if(!assigned)
		{
			if (abs(Xdif) > abs(Ydif))
			{
				walkX = true;
			}
			else
			{
				walkX = false;
			}

			assigned = true;
		}
		
		if (walkX)
		{
			printf("walkX: true\n");
		}
		else
		{
			printf("walkX: false\n");
		}
		
		if (walkX)
		{
			if(abs(Xdif) > 160)
			{
				if (Xdif > 0)
				{
					transform->position.x += 3;
				}
				else
				{
					transform->position.x -= 3;
				}
			}
			else if(abs(Ydif) > 144)
			{
				assigned = false;
				
				if (Ydif > 0)
				{
					transform->position.y += 3;
				}
				else
				{
					transform->position.y -= 3;
				}
			}
			else if (abs(Xdif) > 1)
			{
				if (Xdif > 0)
				{
					transform->position.x += 3;
				}
				else
				{
					transform->position.x -= 3;
				}
			}
			else if (abs(Ydif) > 1)
			{
				if (Ydif > 0)
				{
					transform->position.y += 3;
				}
				else
				{
					transform->position.y -= 3;
				}
			}
		}
		else
		{
			if (abs(Ydif) > 144)
			{
				if (Ydif > 0)
				{
					transform->position.y += 3;
				}
				else
				{
					transform->position.y -= 3;
				}
			}
			else if (abs(Xdif) > 160)
			{
				assigned = false;
				
				if (Xdif > 0)
				{
					transform->position.x += 3;
				}
				else
				{
					transform->position.x -= 3;
				}
			}
			else if (abs(Ydif) > 1)
			{
				if (Ydif > 0)
				{
					transform->position.y += 3;
				}
				else
				{
					transform->position.y -= 3;
				}
			}
			else if (abs(Xdif) > 1)
			{
				if (Xdif > 0)
				{
					transform->position.x += 3;
				}
				else
				{
					transform->position.x -= 3;
				}
			}
		}
		
	}
	else
	{
		assigned = false;
	}
}