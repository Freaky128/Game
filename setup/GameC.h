#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <vector>

class ColliderComponent;

class GameC
{
public:
	GameC();
	~GameC();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void events();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Rect mouseCol(const SDL_Rect& mRect);

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool run;
	static SDL_Rect camera;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupTriColliders
	};

private:
	SDL_Window* window;
};

//static std::vector<ColliderComponent*>colliders;

