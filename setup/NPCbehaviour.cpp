#include "NPCbehaviour.h"
#include "Collision.h"

void NPCbehaviour::update()
{
	NPCIpos = transform->position;

	if (distance == 0)
	{
		distance = rand() % 5000;
		if (distance >= 40 && distance <= 100)
		{
			direction = rand() % 4;
		}
	}

	if (distance >= 40 && distance <= 100)
	{
		if (direction == 0)
		{
			transform->position.y += 1;
			distance--;
			sprite->Play("WalkDown");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else if (direction == 1)
		{
			transform->position.x += 1;
			distance--;
			sprite->Play("WalkRight");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else if (direction == 2)
		{
			transform->position.y += -1;
			distance--;
			sprite->Play("WalkUp");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else
		{
			transform->position.x += -1;
			distance--;
			sprite->Play("WalkLeft");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
	}
	else
	{
		distance = 0;
		if (direction == 0)
		{
			sprite->Play("Idle");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else if (direction == 1)
		{
			sprite->Play("IdleL/R");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else if (direction == 2)
		{
			sprite->Play("IdleUp");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else
		{
			sprite->Play("IdleL/R");
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
		}
	}

	entity->getComponent<ColliderComponent>().update();
	entity->getComponent<SpriteComponent>().update();
}
 

void NPCbehaviour::CollisionDetection(SDL_Rect cCol)
{
	 SDL_Rect NPCcol = NPCcollider->collider;
	 if (Collision::AABB(cCol, NPCcol))
	 {
		 transform->position = NPCIpos;
		 printf("hit NPC\n");
	 }
		
}

void NPCbehaviour::CollisionDetection(SDL_Point sp, SDL_Point fp, char dir)
{
	SDL_Rect NPCcol = NPCcollider->collider;
	if (Collision::AARL(NPCcol, sp, fp, dir))
	{
		transform->position = NPCIpos;
		printf("hit NPC\n");
	}
}