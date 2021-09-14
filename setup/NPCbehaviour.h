#pragma once

#include "Components.h"

class NPCbehaviour : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	ColliderComponent* NPCcollider;
	
	int direction = 0;
	int distance = 0;

public:
	
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		NPCcollider = &entity->getComponent<ColliderComponent>();
	}
	
	Vector2D NPCIpos;
	
	void update() override;
	

	void CollisionDetection(SDL_Rect cCol);
	void CollisionDetection(SDL_Point sp, SDL_Point fp, char dir);
};