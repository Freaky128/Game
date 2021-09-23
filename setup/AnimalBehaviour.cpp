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

		Xdif = 320 - (static_cast<int>(animalPos.x) - GameC::camera.x + (10 * SCALE)); //magic numbers
		Ydif = 288 - (static_cast<int>(animalPos.y) - GameC::camera.y + (11 * SCALE));
		printf("Xdif: %d Ydif: %d\n", Xdif, Ydif);
		printf("destRect.w / 2: %d\n", (destRect.w / 2));

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
					sprite->Play("WalkRight");
				}
				else
				{
					transform->position.x -= 3;
					sprite->Play("WalkLeft");
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
					sprite->Play("WalkDown");
				}
				else
				{
					transform->position.y -= 3;
					sprite->Play("WalkUp");
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
					sprite->Play("WalkRight");
				}
				else
				{
					transform->position.x -= 3;
					sprite->Play("WalkLeft");
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
					sprite->Play("WalkDown");
				}
				else
				{
					transform->position.y -= 3;
					sprite->Play("WalkUp");
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

void AnimalBehaviour::castLine(int x0, int y0, int x1, int y1)
{
	int dx, dy, p, x, y;

	dx = x1 - x0;
	dy = y1 - y0;

	x = x0;
	y = y0;

	p = 2 * dy - dx;

	while (x < x1)
	{
		if (p >= 0)
		{
			//putpixel(x, y, 7);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			//putpixel(x, y, 7);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}