#include "AnimalBehaviour.h"

extern Manager manager; // imports external manager

auto& players_animal(manager.getGroup(GameC::groupPlayers)); // gets group from manager and sets it to a local group varible
auto& colliders_animal(manager.getGroup(GameC::groupColliders));
auto& triColliders_animal(manager.getGroup(GameC::groupTriColliders));

SDL_Rect playerPos;
int playerPosXW, playerPosYH;

void AnimalBehaviour::init() // initilises local class varibles from the animals other componets
{
	transform = &entity->getComponent<TransformComponent>();
	sprite = &entity->getComponent<SpriteComponent>();
	Acollider = &entity->getComponent<ColliderComponent>();
	
	LdestRect = { 0,0,1,1 };
}



void AnimalBehaviour::update()
{
	animalPos = transform->position; // sets specific local varibles from local class varible
	destRect = sprite->destRect;

	if (!playerPosAssigned) // ensures assingment only happens once
	{
		for (auto& p : players_animal) // may need to add a check for so it only writes player // initilises local player position to be used for raycast target
		{
			playerPos = p->getComponent<SpriteComponent>().destRect; // has to be in update loop because the players position is only set in the update loop
			playerPos.x += SCALE;
			playerPos.w -= (2 * SCALE);

			playerPosXW = playerPos.x + playerPos.w;
			playerPosYH = playerPos.y + playerPos.h;

			printf("p.x: %d, p.y: %d, p.w: %d, p.h: %d\n", playerPos.x, playerPos.y, playerPos.w, playerPos.h); // debug
		}

		playerPosAssigned = true;
	}

	destRect.x += GameC::camera.x; // makes the animals position correct realative to normal space
	destRect.y += GameC::camera.y;

	//printf("c.x: %d, c.y: %d, c.w: %d, c.h: %d\n", GameC::camera.x, GameC::camera.y, GameC::camera.w, GameC::camera.h); // debug statments
	//printf("bear c.x: %d, c.y: %d, c.w: %d, c.h: %d\n", destRect.x, destRect.y, destRect.w, destRect.h);
	
	if (Collision::AABB(destRect, GameC::camera)) // checks if the bear is inside the camera area
	{
		if (sprite->playing == "Idle") // sets the eyeOffset which is where rays are cast from relative to the animals origin // this is for the bear only - should probabaly makes this into a seperate function
		{
			eyeOffset.x = (10 * SCALE); // because this is a point assignment could be done in one line // magic numbers but just have to be like that
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

		relativeEyePos.x = static_cast<int>(animalPos.x) - GameC::camera.x + eyeOffset.x; // sets the relative eye position of the bear 
		relativeEyePos.y = static_cast<int>(animalPos.y) - GameC::camera.y + eyeOffset.y;

		if ( (relativeEyePos.x < playerPos.x && relativeEyePos.y < playerPos.y) || (relativeEyePos.x > playerPosXW && relativeEyePos.y > playerPosYH) ) // depending on the position of the bear relative to the player this sets the 
		{																																				// positions the ray casts will go to, to mimick the visible portion of the player
			line1.x = playerPosXW;
			line1.y = playerPos.y;
			line2.x = playerPos.x;
			line2.y = playerPosYH;
		}
		else if ((relativeEyePos.x < playerPos.x && relativeEyePos.y > playerPosYH) || (relativeEyePos.x > playerPosXW && relativeEyePos.y < playerPos.y))
		{
			line1.x = playerPos.x;
			line1.y = playerPos.y;
			line2.x = playerPosXW;
			line2.y = playerPosYH;
		}
		else if (relativeEyePos.x >= playerPos.x && relativeEyePos.x <= playerPosXW && relativeEyePos.y < playerPos.y) // used to be y288 - think it'll work like this // could replace with 2/WINDOW_HEIGHT
		{
			line1.x = playerPos.x;
			line1.y = playerPos.y;
			line2.x = playerPosXW;
			line2.y = playerPos.y;
		}
		else if (relativeEyePos.x >= playerPos.x && relativeEyePos.x <= playerPosXW && relativeEyePos.y > playerPosYH) // used to be y288
		{
			line1.x = playerPos.x;
			line1.y = playerPosYH;
			line2.x = playerPosXW;
			line2.y = playerPosYH;
		}
		else if (relativeEyePos.x < playerPos.x && relativeEyePos.y >= playerPos.y && relativeEyePos.y <= playerPosYH)
		{
			line1.x = playerPos.x;
			line1.y = playerPos.y;
			line2.x = playerPos.x;
			line2.y = playerPosYH;
		}
		else if (relativeEyePos.x > playerPosXW && relativeEyePos.y >= playerPos.y && relativeEyePos.y <= playerPosYH)
		{
			line1.x = playerPosXW;
			line1.y = playerPos.y;
			line2.x = playerPosXW;
			line2.y = playerPosYH;
		}

		//printf("Bear pos start. x: %f, y: %f\n", transform->position.x, transform->position.y);

		if (!castLine(relativeEyePos.x, relativeEyePos.y, line1.x, line1.y) || !castLine(relativeEyePos.x, relativeEyePos.y, line2.x, line2.y)) // casts rays and if they don't hit anything it does the movement functionality
		{
			//printf("xpos: %f ypos: %f\n", animalPos.x, animalPos.y); // for debug

			if (state == 0 || state == 1 || state == 3)
			{
				Xdif = (WINDOW_WIDTH / 2) - (static_cast<int>(animalPos.x) - GameC::camera.x + (18 * SCALE)); // finds rough difference between BEAR and player THIS IS BEAR SPECIFIC // has to be rough otherwise stuffs up code below (I think)
				Ydif = (WINDOW_HEIGHT / 2) - (static_cast<int>(animalPos.y) - GameC::camera.y + (11 * SCALE)); // assumes player is always in the centre (they should be?)
			}
			else
			{
				Xdif = (WINDOW_WIDTH / 2) - (static_cast<int>(animalPos.x) - GameC::camera.x + (10 * SCALE));
				Ydif = (WINDOW_HEIGHT / 2) - (static_cast<int>(animalPos.y) - GameC::camera.y + (13 * SCALE));
			}
			
																										   
			printf("Xdif: %d Ydif: %d\n", Xdif, Ydif);
			//printf("destRect.w / 2: %d\n", (destRect.w / 2));

			if (firstLoop) // upon the bear first seeing the player the movement state is set depending on which coordinate (x or y) has the greater difference. This direction will be moved in first
			{
				if (abs(Xdif) > abs(Ydif))
				{
					if (!x1) {
						state = 1;
					}
					else {
						state = 3;
					}
				}
				else
				{
					if (!x2) {
						state = 2;
						transform->position.x += (8 * SCALE); // magic numbers
						transform->position.y -= (2 * SCALE);
					}
					else {
						state = 4;
						transform->position.x += (8 * SCALE);
						transform->position.y -= (2 * SCALE);
					}
				}

				firstLoop = false;
			}

			if (state == 1 && !x1) // state 1 moves the bear on the x axis until the bear reaches a quarter the width of the window
			{
				if (abs(Xdif) > (WINDOW_WIDTH / 4))
				{
					if (Xdif > 0)
					{
						transform->position.x += bearSpeed;
						sprite->Play("WalkRight");
					}
					else
					{
						transform->position.x -= bearSpeed;
						sprite->Play("WalkLeft");
					}
				}
			}

			if ((abs(Xdif) - 3) <= (WINDOW_WIDTH / 4)) // checks if state 1 is complete // -3 is to account for movement just made. This is flawed as the xdiff will 
			{							// only actually change by three if the player is stationary and the bear is in state 1 or 3. Still works pretty well though / isn't noticeable
				x1 = true;
			}
			else
			{
				x1 = false;
			}

			if (state == 2 && !y1) // state 2 moves the bear on the y axis until the bear reaches a quarter the height of the window
			{
				if (abs(Ydif) > (WINDOW_HEIGHT / 4))
				{

					if (Ydif > 0)
					{
						transform->position.y += bearSpeed;
						sprite->Play("WalkDown");
					}
					else
					{
						transform->position.y -= bearSpeed;
						sprite->Play("WalkUp");
					}
				}
			}

			if ((abs(Ydif) - 3) <= (WINDOW_HEIGHT / 4)) // checks if state 2 is complete // above flaws apply
			{
				y1 = true;
			}
			else
			{
				y1 = false;
			}

			if (state == 3 && !x2) // state 3 moves the bear on the x axis until the bear reaches the centre of the window 
			{
				if (abs(Xdif) > 1)
				{
					if (Xdif > 0)
					{
						transform->position.x += bearSpeed;
						sprite->Play("WalkRight");
					}
					else
					{
						transform->position.x -= bearSpeed;
						sprite->Play("WalkLeft");
					}
				}
			}

			if ((abs(Xdif) - 3) <= 1) // checks if state 3 is complete // above flaws apply
			{
				x2 = true;
			}
			else
			{
				x2 = false;
			}

			if (state == 4 && !y2) // state 4 moves the bear on the y axis until the bear reaches the centre of the window
			{
				if (abs(Ydif) > 1)
				{
					if (Ydif > 0)
					{
						transform->position.y += bearSpeed;
						sprite->Play("WalkDown");
					}
					else
					{
						transform->position.y -= bearSpeed;
						sprite->Play("WalkUp");
					}
				}
			}

			if ((abs(Ydif) - 3) <= 1) // checks if state 4 is complete // above flaws apply
			{
				y2 = true;
			}
			else
			{
				y2 = false;
			}

			printf("state before: %d\n", state); // debug
			
			if (state == 1 && x1) // this is the state comtrol structure. Once the movement is complete this decides which state the bear should be in for next frame.  
			{
				if (!y1) // switches the state between x state and the appropriate y states unless all y states are complete in which case the next x state is selected 
				{
					state = 2;
					transform->position.x += (8 * SCALE); // magic numbers
					transform->position.y -= (2 * SCALE);

					if (Ydif > 0)
					{
						sprite->Play("WalkDown");
					}
					else
					{
						sprite->Play("WalkUp");
					}
				}
				else if(!y2)
				{
					state = 4;
					transform->position.x += (8 * SCALE);
					transform->position.y -= (2 * SCALE);

					if (Ydif > 0)
					{
						sprite->Play("WalkDown");
					}
					else
					{
						sprite->Play("WalkUp");
					}
				}
				else
				{
					state = 3;
				}
			}
			else if (state == 2 && y1) // switches the state between y state and the appropriate x states unless all x states are complete in which case the next y state is selected 
			{
				if (!x1)
				{
					state = 1;
					transform->position.x -= (8 * SCALE);
					transform->position.y += (2 * SCALE);

					if (Xdif > 0)
					{
						sprite->Play("WalkRight");
					}
					else
					{
						sprite->Play("WalkLeft");
					}
				}
				else if (!x2)
				{
					state = 3;
					transform->position.x -= (8 * SCALE);
					transform->position.y += (2 * SCALE);

					if (Xdif > 0)
					{
						sprite->Play("WalkRight");
					}
					else
					{
						sprite->Play("WalkLeft");
					}
				}
				else
				{
					state = 4;
				}
			}
			else if (state == 3 && x2) // switches the state between x state and the appropriate y states
			{
				if (!y1)
				{
					state = 2;
					transform->position.x += (8 * SCALE);
					transform->position.y -= (2 * SCALE);
				}
				else
				{
					state = 4;
					transform->position.x += (8 * SCALE);
					transform->position.y -= (2 * SCALE);
				}

				if (Ydif > 0)
				{
					sprite->Play("WalkDown");
				}
				else
				{
					sprite->Play("WalkUp");
				}
			}
			else if (state == 4 && y2) // switches the state between y state and the appropriate x states
			{
				if (!x1)
				{
					state = 1;
					transform->position.x -= (8 * SCALE);
					transform->position.y += (2 * SCALE);
				}
				else
				{
					state = 3;
					transform->position.x -= (8 * SCALE);
					transform->position.y += (2 * SCALE);
				}

				if (Xdif > 0)
				{
					sprite->Play("WalkRight");
				}
				else
				{
					sprite->Play("WalkLeft");
				}
			}

			if (state == 3 && !x1) // makes sure that if the bear is in a final x state and the x state before it becomes incomplete it switches back to that state 
			{
				state = 1;
			}
			else if (state == 4 && !y1) // makes sure that if the bear is in a final y state and the y state before it becomes incomplete it switches back to that state
			{
				state = 2;
			}

			printf("state after: %d\n", state); // debug
		}
		else // ensure the right animation plays once movement finsihes
		{
			firstLoop = true; // effectively resets the state once the bear can't see the player

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

		//printf("Bear pos end. x: %f, y: %f\n", transform->position.x, transform->position.y);

	}
	else
	{
		firstLoop = true; // effectively resets the state once the bear is off screen
	}
}

bool AnimalBehaviour::castLine(int x1, int y1, int x2, int y2) // ray casting function. returns true if the ray hits a map collider. Returns false if the ray is unobstructed
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