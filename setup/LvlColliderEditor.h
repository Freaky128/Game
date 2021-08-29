#pragma once

#include "GameC.h"

class LvlColliderEditor
{
public:
	static bool mouseDown;
	
	static void update()
	{
		if (!mouseDown)
		{
			if (GameC::event.type == SDL_MOUSEBUTTONDOWN && GameC::event.button.button == SDL_BUTTON_LEFT)
			{
				printf("WTF\n");
				mouseDown = true;

			}
		}
		else
		{
			if (GameC::event.type == SDL_MOUSEBUTTONUP)
			{
				printf("UP\n");
				mouseDown = false;
			}
		}
	}

private:
	
};