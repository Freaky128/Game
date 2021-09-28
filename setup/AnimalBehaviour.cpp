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
		if (sprite->playing == "Idle")
		{
			eyeOffset.x = (10 * SCALE);
			eyeOffset.y = (16 * SCALE);
		}
		else if (sprite->playing == "IdleRight")
		{
			eyeOffset.x = (29 * SCALE);
			eyeOffset.y = (9 * SCALE);
		}
		else if (sprite->playing == "IdleLeft")
		{
			eyeOffset.x = (6 * SCALE);
			eyeOffset.y = (9 * SCALE);
		}
		else if (sprite->playing == "IdleUp")
		{
			eyeOffset.x = (10 * SCALE);
			eyeOffset.y = (4 * SCALE);
		}
		else if (sprite->playing == "WalkDown")
		{
			eyeOffset.x = (10 * SCALE);
			eyeOffset.y = (16 * SCALE);
		}
		else if (sprite->playing == "WalkRight")
		{
			eyeOffset.x = (30 * SCALE);
			eyeOffset.y = (9 * SCALE);
		}
		else if (sprite->playing == "WalkLeft")
		{
			eyeOffset.x = (7 * SCALE);
			eyeOffset.y = (10 * SCALE);
		}
		else if (sprite->playing == "WalkUp")
		{
			eyeOffset.x = (10 * SCALE);
			eyeOffset.y = (4 * SCALE);
		}

		if ( (static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x < 296 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y < 260) || (static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x > 344 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y > 316) )
		{
			line1.x = 340;
			line1.y = 260;
			line2.x = 300;
			line2.y = 316;
		}
		else if ((static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x < 296 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y > 316) || (static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x > 344 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y < 260))
		{
			line1.x = 300;
			line1.y = 260;
			line2.x = 340;
			line2.y = 316;
		}
		else if (static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x >= 296 && static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x <= 344 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y < 288)
		{
			line1.x = 300;
			line1.y = 260;
			line2.x = 340;
			line2.y = 260;
		}
		else if (static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x >= 296 && static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x <= 344 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y > 288)
		{
			line1.x = 300;
			line1.y = 316;
			line2.x = 340;
			line2.y = 316;
		}
		else if (static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x < 320 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y >= 260 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y <= 316)
		{
			line1.x = 300;
			line1.y = 260;
			line2.x = 300;
			line2.y = 316;
		}
		else if (static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x > 320 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y >= 260 && static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y <= 316)
		{
			line1.x = 340;
			line1.y = 260;
			line2.x = 340;
			line2.y = 316;
		}

		if (!castLine(static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x, static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y, line1.x, line1.y) || !castLine(static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x, static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y, line2.x, line2.y))
		{
			//printf("xpos: %f ypos: %f\n", animalPos.x, animalPos.y);

			Xdif = 320 - (static_cast<int>(animalPos.x) - GameC::camera.x + (10 * SCALE)); //magic numbers
			Ydif = 288 - (static_cast<int>(animalPos.y) - GameC::camera.y + (11 * SCALE));
			//printf("Xdif: %d Ydif: %d\n", Xdif, Ydif);
			//printf("destRect.w / 2: %d\n", (destRect.w / 2));

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

			//printf("state: %d\n", state);

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
			else if (state == 2 && y1)
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
			if (sprite->playing == "WalkRight")
			{
				sprite->Play("IdleRight");
			}
			else if(sprite->playing == "WalkLeft")
			{
				sprite->Play("IdleLeft");
			}
			else if (sprite->playing == "WalkDown")
			{
				sprite->Play("Idle");
			}
			else if (sprite->playing == "WalkUp")
			{
				sprite->Play("IdleUp");
			}
		}
	}
	else
	{
		firstLoop = true;
	}
}

bool AnimalBehaviour::castLine(int x1, int y1, int x2, int y2)
{	
	// Bresenham's line algorithm
	const bool steep = (abs(y2 - y1) > abs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const int dx = x2 - x1;
	const int dy = abs(y2 - y1);

	int error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x <= maxX; x++)
	{
		if (steep)
		{
			LdestRect.x = y;
			LdestRect.y = x;
			if (GameC::rayCol(LdestRect))
			{
				return true;
			}
			//SetPixel(y, x, color);
		}
		else
		{
			LdestRect.x = x;
			LdestRect.y = y;
			if (GameC::rayCol(LdestRect))
			{
				return true;
			}
			//SetPixel(x, y, color);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	return false;
}