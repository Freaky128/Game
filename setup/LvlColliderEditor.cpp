#include "LvlColliderEditor.h"
#include "TextureManager.h"
#include "Components.h"

extern Manager manager;

int LvlColliderEditor::ix;
int LvlColliderEditor::iy;

int LvlColliderEditor::fx;
int LvlColliderEditor::fy;

int LvlColliderEditor::x, LvlColliderEditor::y;

SDL_Rect LvlColliderEditor::destR, LvlColliderEditor::srcR;
SDL_Texture* LvlColliderEditor::tex;
bool LvlColliderEditor::mouseDown = false;


void LvlColliderEditor::init()
{
	srcR = { 0,0,32,32 };
	tex = TextureManager::LoadTexture("assets/collider.png");
}

void LvlColliderEditor::update()
{
	
	if (!mouseDown)
	{
		if (GameC::event.type == SDL_MOUSEBUTTONDOWN && GameC::event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&ix, &iy);
			
			ix = (ix - (ix % 4)) + GameC::camera.x;
			iy = (iy - (iy % 4)) + GameC::camera.y;

			printf("ix:%d iy:%d\n", ix, iy);
			mouseDown = true;

		}
	}
	else
	{
		if (GameC::event.type == SDL_MOUSEBUTTONUP)
		{
			SDL_GetMouseState(&fx, &fy);
			
			fx = (fx - (fx % 4)) + GameC::camera.x;
			fy = (fy - (fy % 4)) + GameC::camera.y;
			
			destR.w = (fx - ix);
			destR.h = (fy - iy);
			
			printf("fx:%d fy:%d\n", fx, fy);
			mouseDown = false;
		}
	}

	if (mouseDown)
	{
		SDL_GetMouseState(&x, &y);
		
		x = (x - (x % 4)) + GameC::camera.x;
		y = (y - (y % 4)) + GameC::camera.y;

		printf("x:%d y:%d\n", x, y);
		
		destR.w = (x - ix);
		destR.h = (y - iy);
	}

	destR.x = ix - GameC::camera.x;
	destR.y = iy - GameC::camera.y;

	if (!mouseDown && GameC::event.type == SDL_KEYDOWN && GameC::event.key.keysym.sym == SDLK_k && destR.w != NULL)
	{
		auto& tcol(manager.addEntity());
		tcol.addComponent<ColliderComponent>("terrain", ix, iy, fx - ix, fy - iy);
		tcol.addGroup(GameC::groupColliders);

		printf("added\n");
	}

	//TODO [Matthew] add delete function, add export and delete function, possibly numbering system
}

void LvlColliderEditor::draw()
{
	TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}