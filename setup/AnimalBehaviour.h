#pragma once

#include "Components.h"
#include "Collision.h"

class AnimalBehaviour : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	ColliderComponent* Acollider;
	SDL_Texture* texture;

	SDL_Rect destRect, LsrcRect, LdestRect;

	int Xdif, Ydif;
	bool firstLoop = true;
	bool x1 = false;
	bool y1 = false;
	bool x2 = false;
	bool y2 = false;
	int state = 0;
	

public:
	Vector2D animalPos;
	SDL_Point eyeOffset = { 0,0 };
	SDL_Point line1 = { 320,288 };
	SDL_Point line2 = { 320,288 };

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		Acollider = &entity->getComponent<ColliderComponent>();

		texture = TextureManager::LoadTexture("assets/collider.png");
		LsrcRect = { 0,0,32,32 };
		LdestRect = { 0,0,1,1 };
	}

	void update() override;

	bool castLine(int x1, int y1, int x2, int y2);
};