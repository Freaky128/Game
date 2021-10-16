#pragma once

#include "Components.h"
#include "Vector2D.h"
#include "GameC.h"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int finalHeight = 32;
	int finalWidth = 32;
	int scale = 1;
	
	int speed = 1;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.x = 336;
		position.y = 256;

		scale = sc;
	}
	
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int sc) // 
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	/*TransformComponent(float x, float y, int iw, int ih, int sc) // legacy code
	{
		position.x = x;
		position.y = y;
		height = ih;
		width = iw;
		finalHeight = ih;
		finalWidth = iw;
		scale = sc;
	}*/

	TransformComponent(int w, int h, int sc)
	{
		position.x = (WINDOW_WIDTH / 2) - 24; // magic numbers
		//std::cout << position.x << std::endl;
		position.y = (WINDOW_HEIGHT / 2) - 28;
		//std::cout << position.y << std::endl;
		height = h;
		//std::cout << height << std::endl;
		width = w;
		//std::cout << width << std::endl;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}
	
	void update() override
	{
		
	}

};

