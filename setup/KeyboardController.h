#pragma once

//#include "gameC.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_SPACE])
		{
			transform->velocity.y = -4;
			transform->velocity.x = 0;
			sprite->Play("WalkUp");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else if (currentKeyStates[SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_SPACE])
		{
			transform->velocity.y = 4;
			transform->velocity.x = 0;
			sprite->Play("WalkDown");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else if (currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_SPACE])
		{
			transform->velocity.x = -4;
			transform->velocity.y = 0;
			sprite->Play("WalkLeft");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else if (currentKeyStates[SDL_SCANCODE_D] && currentKeyStates[SDL_SCANCODE_SPACE])
		{
			transform->velocity.x = 4;
			transform->velocity.y = 0;
			sprite->Play("WalkRight");
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		else
		{
			if (currentKeyStates[SDL_SCANCODE_W])
			{
				transform->velocity.y = -2;
				transform->velocity.x = 0;
				sprite->Play("WalkUp");
				sprite->spriteFlip = SDL_FLIP_NONE;
			}
			else if (currentKeyStates[SDL_SCANCODE_S])
			{
				transform->velocity.y = 2;
				transform->velocity.x = 0;
				sprite->Play("WalkDown");
				sprite->spriteFlip = SDL_FLIP_NONE;
			}
			else if (currentKeyStates[SDL_SCANCODE_A])
			{
				transform->velocity.x = -2;
				transform->velocity.y = 0;
				sprite->Play("WalkLeft");
				sprite->spriteFlip = SDL_FLIP_NONE;
			}
			else if (currentKeyStates[SDL_SCANCODE_D])
			{
				transform->velocity.x = 2;
				transform->velocity.y = 0;
				sprite->Play("WalkRight");
				sprite->spriteFlip = SDL_FLIP_NONE;
			}
			else
			{
				if (GameC::event.type == SDL_KEYUP)
				{
					switch (GameC::event.key.keysym.sym)
					{
					case SDLK_w:
						transform->velocity.y = 0;
						sprite->Play("IdleUp");
						sprite->spriteFlip = SDL_FLIP_NONE;
						break;
					case SDLK_a:
						transform->velocity.x = 0;
						sprite->Play("IdleL/R");
						sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
						break;
					case SDLK_d:
						transform->velocity.x = 0;
						sprite->Play("IdleL/R");
						sprite->spriteFlip = SDL_FLIP_NONE;
						break;
					case SDLK_s:
						transform->velocity.y = 0;
						sprite->Play("Idle");
						sprite->spriteFlip = SDL_FLIP_NONE;
						break;
					case SDLK_ESCAPE:
						GameC::run = false;
						break;
					default:
						break;
					}
				}
			}
		}
		
		
		/*if (gameC::event.type == SDL_KEYDOWN) 
		{
			switch (gameC::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("WalkUp");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("WalkLeft");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("WalkRight");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("WalkDown");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}*/

		
	}
};