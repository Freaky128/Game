#include "AnimalBehaviour.h"

void AnimalBehaviour::update()
{
	animalPos = transform->position;
	posRectC = sprite->destRect;

	posRectC.x += GameC::camera.x;
	posRectC.y += GameC::camera.y;

	//printf("c.x: %d, c.y: %d, c.w: %d, c.h: %d\n", GameC::camera.x, GameC::camera.y, GameC::camera.w, GameC::camera.h);
	//printf("bear c.x: %d, c.y: %d, c.w: %d, c.h: %d\n", posRectC.x, posRectC.y, posRectC.w, posRectC.h);
	
	if (Collision::AABB(posRectC, GameC::camera))
	{
		printf("xpos: %f ypos: %f\n", transform->position.x, transform->position.y);
		
		Xdif = 320 - (static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2));
		Ydif = 288 - (static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2));
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
			if((static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) < 160 || (static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) > 480)
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
			else if((static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) < 144 || (static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) > 432)
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
			else if ((static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) < 319 || (static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) > 321)
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
			else if ((static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) < 287 || (static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) > 289)
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
			if ((static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) < 144 || (static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) > 432)
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
			else if ((static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) < 160 || (static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) > 480)
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
			else if ((static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) < 287 || (static_cast<int>(transform->position.y) - GameC::camera.y + (sprite->destRect.h / 2)) > 289)
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
			else if ((static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) < 319 || (static_cast<int>(transform->position.x) - GameC::camera.x + (sprite->destRect.w / 2)) > 321)
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