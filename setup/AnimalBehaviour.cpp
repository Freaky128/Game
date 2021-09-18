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

		if (firstLoop)
		{
			if (abs(Xdif) > abs(Ydif))
			{
				state = 1;
			}
			else
			{
				state = 2;
			}

			firstLoop = false;
		}

		if (state == 1 && !x1)
		{
			if (abs(Xdif) > 160)
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

		if ((abs(Xdif) - 3) <= 160)
		{
			x1 = true;
		}
		else
		{
			x1 = false;
		}

		if (state == 2 && !y1)
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
		}

		if ((abs(Ydif) - 3) <= 144)
		{
			y1 = true;
		}
		else
		{
			y1 = false;
		}

		if (state == 3 && !x2)
		{
			if (abs(Xdif) > 1)
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

		if ((abs(Xdif) - 3) <= 1)
		{
			x2 = true;
		}
		else
		{
			x2 = false;
		}

		if (state == 4 && !y2)
		{
			if (abs(Ydif) > 1)
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

		if ((abs(Ydif) - 3) <= 1)
		{
			y2 = true;
		}
		else
		{
			y2 = false;
		}

		printf("state: %d\n", state);

		if (state == 1 && x1)
		{
			if (!y1)
			{
				state = 2;
			}
			else
			{
				state = 4;
			}
		}
		else if(state == 2 && y1)
		{
			if (!x1)
			{
				state = 1;
			}
			else
			{
				state = 3;
			}
		}
		else if (state == 3 && x2)
		{
			if (!y1)
			{
				state = 2;
			}
			else
			{
				state = 4;
			}
		}
		else if (state == 4 && y2)
		{
			if (!x1)
			{
				state = 1;
			}
			else
			{
				state = 3;
			}
		}
	}
	else
	{
		firstLoop = true;
	}
}