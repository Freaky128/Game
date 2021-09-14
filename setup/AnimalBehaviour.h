#pragma once

#include "Components.h"
#include "Collision.h"

class AnimalBehaviour : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	ColliderComponent* Acollider;

	SDL_Rect posRectC;

	int Xdif, Ydif;
	bool walkX;
	bool assigned;

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