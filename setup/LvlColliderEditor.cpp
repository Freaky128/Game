#include "LvlColliderEditor.h"
#include "TextureManager.h"
#include "Components.h"
#include "Collision.h"

extern Manager manager;

int LvlColliderEditor::ix;
int LvlColliderEditor::iy;

int LvlColliderEditor::fx;
int LvlColliderEditor::fy;

int LvlColliderEditor::x, LvlColliderEditor::y;

SDL_Rect LvlColliderEditor::destR, LvlColliderEditor::srcR;
SDL_Texture* LvlColliderEditor::tex;
bool LvlColliderEditor::mouseDown = false;

std::vector<std::vector<int>> LvlColliderEditor::colVec;

void LvlColliderEditor::init()
{
	srcR = { 0,0,32,32 };
	tex = TextureManager::LoadTexture("assets/collider.png");
}

void LvlColliderEditor::update()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_DELETE])
	{
		if(GameC::event.type == SDL_MOUSEBUTTONDOWN && GameC::event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Rect Col;
			std::vector<std::vector<int>>::iterator it = colVec.begin();
			
			SDL_GetMouseState(&x, &y);

			SDL_Rect mouseRect = { x,y,1,1 };
			
			Col = GameC::mouseCol(mouseRect);

			if (Col.x >= 0 && Col.x <= (1008 * 4)) 
			{
				Col.x += GameC::camera.x;
				Col.y += GameC::camera.y;
			}

			printf("col.x: %d\n", Col.x);
			printf("col.y: %d\n", Col.y);

			for (int i = 0; i < colVec.size(); i++) 
			{
				if (colVec[i][0] == Col.x && colVec[i][1] == Col.y) 
				{
					printf("true\n");
					colVec.erase(it + i);
				}
			}

			for (int j = 0; j < colVec.size(); j++)
			{
				for (int i = 0; i < colVec[j].size(); i++)
				{
					printf("%d\n", colVec[j][i]);
				}
			}
		}
	}
	else
	{
		if (!mouseDown)
		{
			if (GameC::event.type == SDL_MOUSEBUTTONDOWN && GameC::event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&ix, &iy);

				ix = (ix - (ix % 4)) + GameC::camera.x;
				iy = (iy - (iy % 4)) + GameC::camera.y;

				if (GameC::camera.x % 4 != 0)
				{
					ix = ix - 2;
				}
				if (GameC::camera.y % 4 != 0)
				{
					iy = iy - 2;
				}

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

				if (GameC::camera.x % 4 != 0)
				{
					fx = fx - 2;
				}
				if (GameC::camera.y % 4 != 0)
				{
					fy = fy - 2;
				}

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

			if (GameC::camera.x % 4 != 0)
			{
				fx = fx - 2;
			}
			if (GameC::camera.y % 4 != 0)
			{
				fy = fy - 2;
			}

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

			std::vector<int> temp;

			temp.push_back(ix);
			temp.push_back(iy);
			temp.push_back(fx - ix);
			temp.push_back(fy - iy);

			colVec.push_back(temp);
			
			for (int j = 0; j < colVec.size(); j++)
			{
				for (int i = 0; i < colVec[j].size(); i++)
				{
					printf("%d\n", colVec[j][i]);
				}
			}

			printf("added\n");
		}
	}

	//TODO [Matthew] add export function, possibly numbering system - don't think I'll worry
}

void LvlColliderEditor::draw()
{
	TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}