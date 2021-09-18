#pragma once

#include "Components.h"
#include "Collision.h"

class AnimalBehaviour : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	ColliderComponent* Acollider;

	SDL_Rect destRect;

	int Xdif, Ydif;
	bool firstLoop = true;
	bool x1 = false;
	bool y1 = false;
	bool x2 = false;
	bool y2 = false;
	int state = 0;

public:
	Vector2D animalPos;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		Acollider = &entity->getComponent<ColliderComponent>();
	}

	void update() override;
};