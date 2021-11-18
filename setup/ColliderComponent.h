#pragma once

#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;
	SpriteComponent* sprite;

	int Ixpos;
	int Iypos;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int width, int height)
	{
		Ixpos = xpos;
		Iypos = ypos;
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.w = width;
		collider.h = height;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

		//tex = TextureManager::LoadTexture("assets/collider.png");
		srcR = { 0, 0, 32, 32 };
		destR = { collider.x, collider.y, collider.w, collider.h };

		//GameC::colliders.push_back(this);
	}

	void update() override
	{
		if (tag == "player")
		{
			collider.x = static_cast<int>(transform->position.x + SCALE);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = sprite->destRect.w - (SCALE * 2);
			collider.h = sprite->destRect.h;
			destR = { collider.x, collider.y, collider.w, collider.h };
		}
		else if(tag == "terrain")
		{
			collider.x = Ixpos - GameC::camera.x;
			collider.y = Iypos - GameC::camera.y;
			destR.x = collider.x;
			destR.y = collider.y;
		}
		else
		{
			collider.x = transform->position.x - GameC::camera.x;
			collider.y = transform->position.y - GameC::camera.y;
			collider.w = sprite->destRect.w;
			collider.h = sprite->destRect.h / 2;
			destR = { collider.x, collider.y, collider.w, collider.h };
		}
	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};