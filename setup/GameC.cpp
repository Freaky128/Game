/*GameC or game control contains all the main functions for high level game control. These are the function used in the main game loop.
GameC also houses the main manager for the Entity Component System (ECS) and houses the initilisation of core entities, over objects and their components*/
#include "GameC.h"
#include "TextureManager.h"
#include "Components.h"
#include "Map.h"
#include "Collision.h"
#include "LvlColliderEditor.h"
#include "Spawner.h"
#include <sstream>

Map* map;

SDL_Renderer* GameC::renderer = nullptr;

Manager manager; // ECS manager

SDL_Event GameC::event;

SDL_Rect GameC::camera = { 0,0,0,0 };

int FPSc = 0;

//std::vector<ColliderComponent*>GameC::colliders; // legacy code

bool GameC::run = false;

auto& Player(manager.addEntity()); // adds initial entities
//auto& wall(manager.addEntity());
auto& mapTex(manager.addEntity());
auto& NPC(manager.addEntity());
auto& NPC2(manager.addEntity());
auto& purpleTree(manager.addEntity());
auto& tree(manager.addEntity());
auto& FPSlabel(manager.addEntity());

//const char* mapfile = "assets/terrain_ss.png"; // legacy code

GameC::GameC() {

}
GameC::~GameC() {

}

void GameC::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) // main game setup initilisation function. 
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // initilises SDL systems 
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

				if (TTF_Init() < NULL)
				{
					printf("SDL_ttf could not be initilised! TTF_Error: %s\n", TTF_GetError());
				}
				else
				{
					printf("TTF initialised...\n");
					run = true;
				}
				
			}
		}
	}

	srand(time(NULL)); // seeds random number generator

	camera.w = width;
	camera.h = height;

	mapTex.addComponent<MapComponent>("Assets/Wild_area_home2.png", 0, 0, 1008, 800, SCALE); //magic numbers - not sure these ones matter too much // adds the graphical element or texture for the map
	mapTex.addGroup(GameC::groupMap);
	
	//map->LoadMap("assets/map.map", 25, 20); // magic numbers

	map = new Map(); // adds the collidable or physical elements of the map
	map->LoadCollidersRect("Assets/colliders_rect.txt", SCALE);
	map->LoadCollidersTri("Assets/colliders_tri.txt", SCALE);
	
	Player.addComponent<TransformComponent>(12, 14, SCALE); // magic numbers - not too sure how to get rid of them, could add a heap of macros // adds nessaccy components to the entities
	Player.addComponent<SpriteComponent>("Assets/T_sprite_sheet.png", true, "Player");
	Player.addComponent<KeyboardController>();
	Player.addComponent<ColliderComponent>("player");
	Player.addGroup(groupPlayers);

	NPC.addComponent<TransformComponent>((368 * SCALE), (412 * SCALE), 12, 14, SCALE); // magic numbers
	NPC.addComponent<SpriteComponent>("Assets/NPC_sprite_sheet.png", true, "NPC");
	NPC.addComponent<ColliderComponent>("NPC");
	NPC.addComponent<NPCbehaviour>();
	NPC.addGroup(groupNPC);

	NPC2.addComponent<TransformComponent>((360 * SCALE), (412 * SCALE), 12, 14, SCALE); // magic numbers
	NPC2.addComponent<SpriteComponent>("Assets/NPC_sprite_sheet.png", true, "NPC");
	NPC2.addComponent<ColliderComponent>("NPC");
	NPC2.addComponent<NPCbehaviour>();
	NPC2.addGroup(groupNPC);

	purpleTree.addComponent<TransformComponent>((540 * SCALE), (358 * SCALE), 48, 26, SCALE); // magic numbers
	purpleTree.addComponent<SpriteComponent>("Assets/purple_tree.png", false, "over object");
	purpleTree.addGroup(groupOverObject);

	tree.addComponent<TransformComponent>((325 * SCALE), (336 * SCALE), 22, 19, SCALE); // magic numbers
	tree.addComponent<SpriteComponent>("Assets/tree_top.png", false, "over object");
	tree.addGroup(groupOverObject);

	SDL_Color white = { 255,255,255,255 };

	FPSlabel.addComponent<UILabel>(0, 0, 16, "test string", "Assets/Helvetica.ttf", white);
	FPSlabel.addGroup(groupHUD);

	camera.x = (434 * SCALE) - ((WINDOW_WIDTH / 2) - 24); //magic numbers
	camera.y = (400 * SCALE) - ((WINDOW_HEIGHT / 2) - 28);

	//wall.addComponent<TransformComponent>(300.0f, 300.0f, 20, 300, 1); // legacy code
	//wall.addComponent<SpriteComponent>("assets/collider.png");
	//wall.addComponent<ColliderComponent>("Wall");
	//wall.addGroup(groupMap);

	LvlColliderEditor::init();

	printf("Ticks per seconds: %lu\n", SDL_GetPerformanceFrequency());
}

auto& mapStuff(manager.getGroup(GameC::groupMap));
auto& players(manager.getGroup(GameC::groupPlayers));
auto& enemies(manager.getGroup(GameC::groupEnemies));
auto& colliders(manager.getGroup(GameC::groupColliders));
auto& triColliders(manager.getGroup(GameC::groupTriColliders));
auto& NPCs(manager.getGroup(GameC::groupNPC));
auto& overObjects(manager.getGroup(GameC::groupOverObject));
auto& HUD(manager.getGroup(GameC::groupHUD));

void GameC::events() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		run = false;
		break;
	}

}


void GameC::update() {

	Spawner::spawnBear();
	
	SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider; // records the position of the players collider
	SDL_Rect cameraPos = camera; // records initial position of the camera

	std::stringstream FPSs;
	FPSs << "FPS: " << FPSc;
	
	FPSlabel.getComponent<UILabel>().SetLabelText(FPSs.str());

	Vector2D pVel = Player.getComponent<TransformComponent>().velocity; // sets player velocity and speed
	const int pSpeed = Player.getComponent<TransformComponent>().speed;
	
	camera.x += (pVel.x * pSpeed); // moves the camera according to player velocity making it appear as though the player is moving
	camera.y += (pVel.y * pSpeed); // because manager has not yet updated this interation of the loop, velocity will be leftover from last loop/frame.
								   // effectively there is a frame lag between key press and start of movement. This should be a 16.66ms delay. Human reaction time is 250ms so probably neglegable

	//manager.refresh();// might not need these could just update collider positions?
	//manager.update();

	for (auto& n : NPCs) // updates colliders positions after camera movement [note]: movement is not confirmed nor rendered yet
	{
		n->getComponent<ColliderComponent>().update();
	}

	for (auto& c : colliders)
	{
		c->getComponent<ColliderComponent>().update();
	}
	for (auto& t : triColliders)
	{
		t->getComponent<ColliderComponentTri>().update();
	}
	for (auto& e : enemies)
	{
		e->getComponent<ColliderComponent>().update();
	}
	
	for (auto& t : triColliders) // tests for collision of player with triColliders. If collision occurs the camera is reset to its initial position before movement
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
	
	for (auto& c : colliders) // tests for collision of player with rectColliders. If collision occurs the camera is reset to its initial position before movement
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			camera.x = cameraPos.x;
			camera.y = cameraPos.y;
			printf("hit\n");
		}
	}

	for (auto& e : NPCs) // tests for collision of player with NPCs. If collision occurs the camera is reset to its initial position before movement
	{
		SDL_Rect NPCcol = e->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(NPCcol, playerCol))
		{
			camera.x = cameraPos.x;
			camera.y = cameraPos.y;
			printf("hit\n");
		}
	}

	manager.refresh(); // deletes any entities made inactive
	manager.update(); // now that the camera position is confirmed the update function of all attached components is called.

	LvlColliderEditor::update(); // updates the in game level collider editor

	//printf("c.x: %d, c.y: %d, c.w: %d, c.h: %d\n", camera.x, camera.y, camera.w, camera.h); // debugging info about camera

}

void GameC::render() {
	SDL_RenderClear(renderer);
	for (auto& m : mapStuff)
	{
		m->draw();
	}
	for (auto& n : NPCs)
	{
		n->draw();
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

	for (auto& o : overObjects)
	{
		o->draw();
	}
	
	for (auto& e : enemies)
	{
		SDL_RenderDrawLine(GameC::renderer, static_cast<int>(e->getComponent<TransformComponent>().position.x) - GameC::camera.x + e->getComponent<AnimalBehaviour>().eyeOffset.x, static_cast<int>(e->getComponent<TransformComponent>().position.y) - GameC::camera.y + e->getComponent<AnimalBehaviour>().eyeOffset.y, e->getComponent<AnimalBehaviour>().line1.x, e->getComponent<AnimalBehaviour>().line1.y);
		SDL_RenderDrawLine(GameC::renderer, static_cast<int>(e->getComponent<TransformComponent>().position.x) - GameC::camera.x + e->getComponent<AnimalBehaviour>().eyeOffset.x, static_cast<int>(e->getComponent<TransformComponent>().position.y) - GameC::camera.y + e->getComponent<AnimalBehaviour>().eyeOffset.y, e->getComponent<AnimalBehaviour>().line2.x, e->getComponent<AnimalBehaviour>().line2.y);
	}

	for (auto& h : HUD)
	{
		h->draw();
	}

	LvlColliderEditor::draw();

	SDL_RenderPresent(renderer);	
}

void GameC::clean() {
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
	for (auto& e : enemies)
	{
		e->destroy();
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

void GameC::getFPS(int FPS)
{
	FPSc = FPS;
}

SDL_Rect GameC::mouseColRect(const SDL_Rect& mRect)
{
	SDL_Rect Col = { -1,-1,-1,-1 };

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

	return Col;
}

SDL_Point GameC::mouseColTri(const SDL_Rect& mRect)
{
	SDL_Point sp = { -1,- 1 };

	for (auto& t : triColliders)
	{
		SDL_Point tSPoint = t->getComponent<ColliderComponentTri>().startP;
		SDL_Point tFPoint = t->getComponent<ColliderComponentTri>().finalP;
		char tDir = t->getComponent<ColliderComponentTri>().direction;
		if (Collision::AARL(mRect, tSPoint, tFPoint, tDir)) // is this over complicated? could i just pass in the whole entity or component or something
		{
			sp = t->getComponent<ColliderComponentTri>().startP;
			t->destroy();
			return sp;
		}
	}

	return sp;
}

bool GameC::rayCol(const SDL_Rect& rRect)
{
	for (auto& t : triColliders)
	{
		SDL_Point tSP = t->getComponent<ColliderComponentTri>().startP;
		SDL_Point tFP = t->getComponent<ColliderComponentTri>().finalP;
		char dir = t->getComponent<ColliderComponentTri>().direction;
		if (Collision::AARL(rRect, tSP, tFP, dir))
		{
			//printf("ray hit\n");
			return true;
		}
	}

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, rRect))
		{
			//printf("ray hit\n");
			return true;
		}
	}

	return false;
}