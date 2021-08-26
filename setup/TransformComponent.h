#pragma once

#include "Components.h"
#include "Vector2D.h"

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

	TransformComponent(float x, float y, int iw, int ih, int fw, int fh, int sc)
	{
		position.x = x;
		position.y = y;
		height = ih;
		width = iw;
		finalHeight = fh;
		finalWidth = fw;
		scale = sc;
	}

	/*TransformComponent(float x, float y, int iw, int ih, int sc)
	{
		position.x = x;
		position.y = y;
		height = ih;
		width = iw;
		finalHeight = ih;
		finalWidth = iw;
		scale = sc;
	}*/

	TransformComponent(int iw, int ih, int fw, int fh, int sc)
	{
		position.x = 308; // magic numbers
		//std::cout << position.x << std::endl;
		position.y = 274;
		//std::cout << position.y << std::endl;
		height = ih;
		//std::cout << height << std::endl;
		width = iw;
		//std::cout << width << std::endl;
		finalHeight = fh;
		//std::cout << finalHeight << std::endl;
		finalWidth = fw;
		//std::cout << finalWidth << std::endl;
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

