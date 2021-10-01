#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <vector>
#include <time.h>

#define SCALE 4
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 576

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

	static SDL_Rect mouseColRect(const SDL_Rect& mRect);
	static SDL_Point mouseColTri(const SDL_Rect& mRect);

	static bool rayCol(const SDL_Rect& rRect);

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool run;
	static SDL_Rect camera;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupNPC,
		groupColliders,
		groupTriColliders,
		groupOverObject
	};

private:
	SDL_Window* window;
};

//static std::vector<ColliderComponent*>colliders;

