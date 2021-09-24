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
	SDL_Rect srcRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	

public:
	const char* playing;
	
	SDL_Rect destRect;

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

		if (tag == "Player" || tag == "NPC")
		{
			playerAnimations();
		}
		else
		{
			bearAnimations();
		}
		
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
			srcRect = animations[playing].framePos[static_cast<int>((SDL_GetTicks() / speed) % frames)];
		}

		if (tag == "Player")
		{
			destRect.x = static_cast<int>(transform->position.x);
			destRect.y = static_cast<int>(transform->position.y);
			destRect.w = srcRect.w * transform->scale;
			destRect.h = srcRect.h * transform->scale;
		}
		else 
		{
			destRect.x = (static_cast<int>(transform->position.x)) - GameC::camera.x;
			destRect.y = (static_cast<int>(transform->position.y)) - GameC::camera.y;
			destRect.w = srcRect.w * transform->scale;
			destRect.h = srcRect.h * transform->scale;
		}

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		speed = animations[animName].speed;
		playing = animName;
	}

	void playerAnimations()
	{
		SDL_Rect temp;
		std::vector<SDL_Rect> rects;
		int frames;
		int speed = 125;

		frames = 1;
		temp = { 0,0,12,14 };
		rects.push_back(temp);
		Animation idle = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,14,12,14 };
		rects.push_back(temp);

		temp = { 12,14,12,14 };
		rects.push_back(temp);
		Animation walkRight = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,28,12,14 };
		rects.push_back(temp);

		temp = { 12,28,12,14 };
		rects.push_back(temp);
		Animation walkLeft = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,42,12,14 };
		rects.push_back(temp);

		temp = { 12,42,12,14 };
		rects.push_back(temp);
		Animation walkDown = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,56,12,14 };
		rects.push_back(temp);

		temp = { 12,56,12,14 };
		rects.push_back(temp);
		Animation walkUp = Animation(frames, speed, rects);

		rects.clear();

		frames = 1;
		temp = { 0,70,12,14 };
		rects.push_back(temp);
		Animation idleUp = Animation(frames, speed, rects);

		rects.clear();

		frames = 1;
		temp = { 0,84,12,14 };
		rects.push_back(temp);
		Animation idleLR = Animation(frames, speed, rects);

		animations.emplace("Idle", idle);
		animations.emplace("WalkRight", walkRight);
		animations.emplace("WalkLeft", walkLeft);
		animations.emplace("WalkDown", walkDown);
		animations.emplace("WalkUp", walkUp);
		animations.emplace("IdleUp", idleUp);
		animations.emplace("IdleL/R", idleLR);
	}

	void bearAnimations()
	{
		SDL_Rect temp;
		std::vector<SDL_Rect> rects;
		int frames;
		int speed = 200;

		frames = 1;
		temp = { 0,0,20,27 };
		rects.push_back(temp);
		Animation idle = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,27,20,27 };
		rects.push_back(temp);

		temp = { 20,27,20,27 };
		rects.push_back(temp);
		Animation walkDown = Animation(frames, speed, rects);

		rects.clear();

		frames = 1;
		temp = { 0,54,20,27 };
		rects.push_back(temp);
		Animation idleUp = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,81,20,27 };
		rects.push_back(temp);

		temp = { 20,81,20,27 };
		rects.push_back(temp);
		Animation walkUp = Animation(frames, speed, rects);

		rects.clear();

		frames = 1;
		temp = { 0,108,34,22 };
		rects.push_back(temp);
		Animation  idleLeft = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,130,35,22 };
		rects.push_back(temp);

		temp = { 35,130,35,22 };
		rects.push_back(temp);
		Animation walkLeft = Animation(frames, speed, rects);

		rects.clear();

		frames = 1;
		temp = { 0,152,34,22 };
		rects.push_back(temp);
		Animation idleRight = Animation(frames, speed, rects);

		rects.clear();

		frames = 2;
		temp = { 0,174,37,22 };
		rects.push_back(temp);

		temp = { 37,174,35,22 };
		rects.push_back(temp);
		Animation walkRight = Animation(frames, speed, rects);

		animations.emplace("Idle", idle);
		animations.emplace("WalkRight", walkRight);
		animations.emplace("WalkLeft", walkLeft);
		animations.emplace("WalkDown", walkDown);
		animations.emplace("WalkUp", walkUp);
		animations.emplace("IdleUp", idleUp);
		animations.emplace("IdleRight", idleRight);
		animations.emplace("IdleLeft", idleLeft);
	}
};