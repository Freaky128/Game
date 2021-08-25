#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::string tag;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated, std::string t)
	{
		animated = isAnimated;

		tag = t;

		Animation idle = Animation(0, 1, 1);
		Animation walkRight = Animation(1, 2, 125);
		Animation walkLeft = Animation(2, 2, 125);
		Animation walkDown = Animation(3, 2, 125);
		Animation walkUp = Animation(4, 2, 125);
		Animation idleUp = Animation(5, 1, 1);
		Animation idleLR = Animation(6, 1, 1);

		animations.emplace("Idle", idle);
		animations.emplace("WalkRight", walkRight);
		animations.emplace("WalkLeft", walkLeft);
		animations.emplace("WalkDown", walkDown);
		animations.emplace("WalkUp", walkUp);
		animations.emplace("IdleUp", idleUp);
		animations.emplace("IdleL/R", idleLR);

		Play("Idle");

		setTex(path);
	}
	
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}
	
	void init() override
	{
		
		transform = &entity->getComponent<TransformComponent>();
		
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = transform->width;
		//std::cout << srcRect.w << std::endl;
		srcRect.h = transform->height;
		//std::cout << srcRect.h << std::endl;
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		
		srcRect.y = animIndex * transform->height;

		if (tag == "Player")
		{
			destRect.x = static_cast<int>(transform->position.x);
			destRect.y = static_cast<int>(transform->position.y);
			destRect.w = transform->finalWidth * transform->scale;
			destRect.h = transform->finalHeight * transform->scale;
		}
		else 
		{
			destRect.x = (static_cast<int>(transform->position.x)) - GameC::camera.x;
			destRect.y = (static_cast<int>(transform->position.y)) - GameC::camera.y;
			destRect.w = transform->finalWidth * transform->scale;
			destRect.h = transform->finalHeight * transform->scale;
		}

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};