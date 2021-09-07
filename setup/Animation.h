#pragma once

struct Animation
{
	int frames;
	int speed;
	std::vector<SDL_Rect> framePos;

	Animation() {}

	Animation(int f, int s, std::vector<SDL_Rect> rects)
	{
		frames = f;
		speed = s;
		framePos.swap(rects);
		/*printf("%d\n", framePos[0].y);
		if (framePos.size() > 1)
		{
			printf("%d\n", framePos[1].y);
		}*/
	}

};