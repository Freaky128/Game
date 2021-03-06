#include "NPCbehaviour.h"
#include "Collision.h"

extern Manager manager;

auto& colliders_NPC(manager.getGroup(GameC::groupColliders));
auto& triColliders_NPC(manager.getGroup(GameC::groupTriColliders));
auto& players_NPC(manager.getGroup(GameC::groupPlayers));

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
	
	entity->getComponent<ColliderComponent>().update(); // hit box will temporarily appear to clip into colliding object however should not have an effect

	for (auto& c : colliders_NPC)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		CollisionDetection(cCol);
	}

	for (auto& t : triColliders_NPC)
	{
		SDL_Point sp = t->getComponent<ColliderComponentTri>().startP;
		SDL_Point fp = t->getComponent<ColliderComponentTri>().finalP;
		char dir = t->getComponent<ColliderComponentTri>().direction;
		CollisionDetection(sp, fp, dir);
	}

	for (auto& p : players_NPC) // tests for collision of NPCs with the player
	{
		CollisionDetection(p->getComponent<ColliderComponent>().collider);
	}

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