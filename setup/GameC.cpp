#include "GameC.h"
#include "TextureManager.h"
#include "Components.h"
#include "Map.h"
#include "Collision.h"
#include "LvlColliderEditor.h"

#define SCALE 4

Map* map;

SDL_Renderer* GameC::renderer = nullptr;

Manager manager;

SDL_Event GameC::event;

SDL_Rect GameC::camera = { 0,0,0,0 };

//std::vector<ColliderComponent*>GameC::colliders;

bool GameC::run = false;

auto& Player(manager.addEntity());
//auto& wall(manager.addEntity());
auto& mapTex(manager.addEntity());
auto& NPC(manager.addEntity());
auto& NPC2(manager.addEntity());

//const char* mapfile = "assets/terrain_ss.png";

GameC::GameC() {

}
GameC::~GameC() {

}

void GameC::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		run = false;
	}
	else {
		printf("SDL initialised...\n");

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			run = false;
		}
		else {
			printf("Window created...\n");

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				run = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				printf("Renderer created...\n");

				run = true;
			}
		}
	}

	camera.w = width;
	camera.h = height;

	mapTex.addComponent<MapComponent>("Assets/Wild_area_home2.png", 0, 0, 1008, 800, SCALE);//magic numbers
	mapTex.addGroup(GameC::groupMap);
	
	//map->LoadMap("assets/map.map", 25, 20); // magic numbers

	map = new Map();
	map->LoadCollidersRect("assets/colliders_rect.txt", SCALE);
	map->LoadCollidersTri("assets/colliders_tri.txt", SCALE);
	
	Player.addComponent<TransformComponent>(12,14,12,14,SCALE); // magic numbers
	Player.addComponent<SpriteComponent>("Assets/T_sprite_sheet.png", true, "Player");
	Player.addComponent<KeyboardController>();
	Player.addComponent<ColliderComponent>("player");
	Player.addGroup(groupPlayers);

	NPC.addComponent<TransformComponent>((366 * SCALE),(410 * SCALE),12,14,12,14,SCALE); // magic numbers
	NPC.addComponent<SpriteComponent>("Assets/NPC_sprite_sheet.png", true, "NPC");
	NPC.addComponent<ColliderComponent>("NPC");
	NPC.addComponent<NPCbehaviour>();
	NPC.addGroup(groupEnemies);

	NPC2.addComponent<TransformComponent>((360 * SCALE), (410 * SCALE), 12, 14, 12, 14, SCALE); // magic numbers
	NPC2.addComponent<SpriteComponent>("Assets/NPC_sprite_sheet.png", true, "NPC");
	NPC2.addComponent<ColliderComponent>("NPC");
	NPC2.addComponent<NPCbehaviour>();
	NPC2.addGroup(groupEnemies);

	camera.x = (434 * SCALE) - 308; //magic numbers
	camera.y = (400 * SCALE) - 274;

	//wall.addComponent<TransformComponent>(300.0f, 300.0f, 20, 300, 1);
	//wall.addComponent<SpriteComponent>("assets/collider.png");
	//wall.addComponent<ColliderComponent>("Wall");
	//wall.addGroup(groupMap);

	LvlColliderEditor::init();
}

auto& mapStuff(manager.getGroup(GameC::groupMap));
auto& players(manager.getGroup(GameC::groupPlayers));
auto& enemies(manager.getGroup(GameC::groupEnemies));
auto& colliders(manager.getGroup(GameC::groupColliders));
auto& triColliders(manager.getGroup(GameC::groupTriColliders));

void GameC::events() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		run = false;
		break;
	}

}

void GameC::update() {

	SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
	SDL_Rect cameraPos = camera;
	
	//manager.refresh();
	//manager.update();

	Vector2D pVel = Player.getComponent<TransformComponent>().velocity;
	const int pSpeed = Player.getComponent<TransformComponent>().speed;
	
	camera.x += (pVel.x * pSpeed);
	camera.y += (pVel.y * pSpeed);

	//manager.refresh();// might not need these could just update collider positions?
	//manager.update();

	for (auto& e : enemies)
	{
		e->getComponent<ColliderComponent>().update();
	}

	for (auto& c : colliders)
	{
		c->getComponent<ColliderComponent>().update();
	}
	for (auto& t : triColliders)
	{
		t->getComponent<ColliderComponentTri>().update();
	}
	
	for (auto& t : triColliders)
	{
		SDL_Point tSP = t->getComponent<ColliderComponentTri>().startP;
		SDL_Point tFP = t->getComponent<ColliderComponentTri>().finalP;
		char dir = t->getComponent<ColliderComponentTri>().direction;
		if (Collision::AARL(playerCol, tSP, tFP, dir))
		{
			camera.x = cameraPos.x;
			camera.y = cameraPos.y;
			printf("hit tri\n");
		}
	}
	
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			camera.x = cameraPos.x;
			camera.y = cameraPos.y;
			printf("hit\n");
		}
	}

	for (auto& e : enemies)
	{
		SDL_Rect NPCcol = e->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(NPCcol, playerCol))
		{
			camera.x = cameraPos.x;
			camera.y = cameraPos.y;
			printf("hit\n");
		}
	}

	manager.update();
	manager.refresh();

	for (auto& e : enemies)
	{
		for (auto& c : colliders)
		{
			SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
			e->getComponent<NPCbehaviour>().CollisionDetection(cCol);
		}
	}

	for (auto& e : enemies)
	{
		for (auto& t : triColliders)
		{
			SDL_Point sp = t->getComponent<ColliderComponentTri>().startP;
			SDL_Point fp = t->getComponent<ColliderComponentTri>().finalP;
			char dir = t->getComponent<ColliderComponentTri>().direction;
			e->getComponent<NPCbehaviour>().CollisionDetection(sp, fp, dir);
		}
	}

	for (auto& e : enemies)
	{
			e->getComponent<NPCbehaviour>().CollisionDetection(playerCol);		
	}

	LvlColliderEditor::update();

	/*for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}*/
}

void GameC::render() {
	SDL_RenderClear(renderer);
	for (auto& m : mapStuff)
	{
		m->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& c : colliders)  
	{
		c->draw();
	}
	for (auto& t : triColliders)
	{
		t->draw();
	}

	LvlColliderEditor::draw();

	SDL_RenderPresent(renderer);
}

void GameC::clean() {
	/*delete& Player;
	delete& NPC;
	delete& NPC2;
	delete& NPC3;
	for (auto& c : colliders) // throws exception i think
	{
		delete c;
	}*/
	
	Player.destroy();
	NPC.destroy();
	NPC2.destroy();
	mapTex.destroy();
	delete map;
	for (auto& c : colliders)
	{
		c->destroy();
	}
	for (auto& t : triColliders)
	{
		t->destroy();
	}

	manager.refresh();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("cleaning complete...\n");
}

bool GameC::running() {
	return run; 
}

SDL_Rect GameC::mouseColRect(const SDL_Rect& mRect)
{
	SDL_Rect Col;

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, mRect))
		{
			Col = c->getComponent<ColliderComponent>().collider;
			c->destroy();
			return Col;
		}
	}
}

SDL_Point GameC::mouseColTri(const SDL_Rect& mRect)
{
	SDL_Point sp;

	for (auto& t : triColliders)
	{
		SDL_Point tSPoint = t->getComponent<ColliderComponentTri>().startP;
		SDL_Point tFPoint = t->getComponent<ColliderComponentTri>().finalP;
		char tDir = t->getComponent<ColliderComponentTri>().direction;
		if (Collision::AARL(mRect, tSPoint, tFPoint, tDir))
		{
			sp = t->getComponent<ColliderComponentTri>().startP;
			t->destroy();
			return sp;
		}
	}
}