#define _CRT_SECURE_NO_WARNINGS

#include "LvlColliderEditor.h"
#include "TextureManager.h"
#include "Components.h"
#include "Collision.h"
#include <fstream>
#include <cmath>

extern Manager manager;

int LvlColliderEditor::ix;
int LvlColliderEditor::iy;

int LvlColliderEditor::fx;
int LvlColliderEditor::fy;

int LvlColliderEditor::x, LvlColliderEditor::y;

int LvlColliderEditor::mode = 0;

SDL_Rect LvlColliderEditor::destR, LvlColliderEditor::srcR;
SDL_Texture* LvlColliderEditor::tex;
bool LvlColliderEditor::mouseDown = false;

std::vector<std::vector<int>> LvlColliderEditor::colVec;
std::vector<std::vector<int>> LvlColliderEditor::triColVec;

void LvlColliderEditor::init()
{
	srcR = { 0,0,32,32 };
	tex = TextureManager::LoadTexture("assets/collider.png");
}

void LvlColliderEditor::update()
{
	if (GameC::event.type == SDL_KEYDOWN && GameC::event.key.keysym.sym == SDLK_m)
	{
		if (mode == 0)
		{
			mode = 1;
			printf("Tri mode\n");
		}
		else
		{
			mode = 0;
			printf("Rect mode\n");
		}
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	if (mode == 0)
	{
		if (currentKeyStates[SDL_SCANCODE_DELETE])
		{
			if (GameC::event.type == SDL_MOUSEBUTTONDOWN && GameC::event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_Rect Col;
				std::vector<std::vector<int>>::iterator it = colVec.begin();

				SDL_GetMouseState(&x, &y);

				SDL_Rect mouseRect = { x,y,1,1 };

				Col = GameC::mouseColRect(mouseRect);

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
					x = x - 2;
				}
				if (GameC::camera.y % 4 != 0)
				{
					y = y - 2;
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
	}
	else // tri mode
	{
		if (currentKeyStates[SDL_SCANCODE_DELETE])
		{
			if (GameC::event.type == SDL_MOUSEBUTTONDOWN && GameC::event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_Point sp;
				std::vector<std::vector<int>>::iterator it = triColVec.begin();

				SDL_GetMouseState(&x, &y);

				SDL_Rect mouseRect = { x,y,1,1 };

				sp = GameC::mouseColTri(mouseRect);

				if (sp.x >= 0 && sp.x <= (1008 * 4))
				{
					sp.x += GameC::camera.x;
					sp.y += GameC::camera.y;
				}

				printf("sp.x: %d\n", sp.x);
				printf("sp.y: %d\n", sp.y);

				for (int i = 0; i < triColVec.size(); i++)
				{
					if (triColVec[i][0] == sp.x && triColVec[i][1] == sp.y)
					{
						printf("true\n");
						triColVec.erase(it + i);
					}
				}

				for (int j = 0; j < triColVec.size(); j++)
				{
					for (int i = 0; i < triColVec[j].size(); i++)
					{
						printf("%d\n", triColVec[j][i]);
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

					if ((fy - iy) < 0)
					{
						if ((fx - ix) < (iy - fy))
						{
							fx += (iy - fy) - (fx - ix);
						}
						else if ((fx - ix) > (iy - fy))
						{
							fy -= (fx - ix) - (iy - fy);
						}
					}
					else
					{
						if ((fx - ix) < (fy - iy))
						{
							fx += (fy - iy) - (fx - ix);
						}
						else if ((fx - ix) > (fy - iy))
						{
							fy += (fx - ix) - (fy - iy);
						}
					}

					destR.w = (fx - ix);
					destR.h = abs((fy - iy));

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
					x = x - 2;
				}
				if (GameC::camera.y % 4 != 0)
				{
					y = y - 2;
				}


				if ((y - iy) < 0)
				{
					if ((x - ix) < (iy - y))
					{
						x += (iy - y) - (x - ix);
					}
					else if ((x - ix) > (iy - y))
					{
						y -= (x - ix) - (iy - y);
					}
				}
				else
				{
					if ((x - ix) < (y - iy))
					{
						x += (y - iy) - (x - ix);
					}
					else if ((x - ix) > (y - iy))
					{
						y += (x - ix) - (y - iy);
					}
				}

				printf("x:%d y:%d\n", x, y);

				destR.w = (x - ix);
				destR.h = abs((y - iy));
			}

			if (iy > y)
			{
				destR.y = y - GameC::camera.y;
			}
			else
			{
				destR.y = iy - GameC::camera.y;
			}
			destR.x = ix - GameC::camera.x;


			if (!mouseDown && GameC::event.type == SDL_KEYDOWN && GameC::event.key.keysym.sym == SDLK_k && destR.w != NULL)
			{
				char direction;
				if (fy > iy)
				{
					direction = 'd';
					fx -= 4;
					fy -= 4;
				}
				else
				{
					direction = 'u';
					iy -= 4;
					fx -= 4;
					fy -= 4;
				}

				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponentTri>(direction, ix, iy, fx, fy, 4);
				tcol.addGroup(GameC::groupTriColliders);

				std::vector<int> temp;

				temp.push_back(ix);
				temp.push_back(iy);
				temp.push_back(fx);
				temp.push_back(fy);

				triColVec.push_back(temp);

				for (int j = 0; j < triColVec.size(); j++)
				{
					for (int i = 0; i < triColVec[j].size(); i++)
					{
						printf("%d\n", triColVec[j][i]);
					}
				}

				printf("added\n");
			}
		}
	}

}

void LvlColliderEditor::writeRect()
{
	int index1;
	int index2;
	char buffer [16];
	
	FILE* colliderFileRectW;
	colliderFileRectW = fopen("assets/colliders_rect_write.txt","a");

	for (index1 = 0; index1 < colVec.size(); index1++)
	{
		for (index2 = 0; index2 < 4; index2++)
		{
			if ((colVec[index1][index2] / 4) < 1000)
			{
				fputs("0", colliderFileRectW);
				if ((colVec[index1][index2] / 4) < 100)
				{
					fputs("0", colliderFileRectW);
					if ((colVec[index1][index2] / 4) < 10)
					{
						fputs("0", colliderFileRectW);
					}
				}
			}
			
			sprintf(buffer, "%d", (colVec[index1][index2] / 4));
			fputs(buffer, colliderFileRectW);
			
			if (index2 < 3) 
			{
				fputs(",", colliderFileRectW);
			}
		}
		fputs("\n", colliderFileRectW);
	}

	printf("done\n");
	fclose(colliderFileRectW);
}

void LvlColliderEditor::writeTri()
{
	int index1;
	int index2;
	char buffer[16];

	FILE* colliderFileTriW;
	colliderFileTriW = fopen("assets/colliders_tri_write.txt", "a");

	for (index1 = 0; index1 < triColVec.size(); index1++)
	{
		if (triColVec[index1][1] < triColVec[index1][3])
		{
			fputs("d", colliderFileTriW);
		}
		else
		{
			fputs("u", colliderFileTriW);
		}

		fputs(",", colliderFileTriW);
		
		for (index2 = 0; index2 < 4; index2++)
		{
			if ((triColVec[index1][index2] / 4) < 1000)
			{
				fputs("0", colliderFileTriW);
				if ((triColVec[index1][index2] / 4) < 100)
				{
					fputs("0", colliderFileTriW);
					if ((triColVec[index1][index2] / 4) < 10)
					{
						fputs("0", colliderFileTriW);
					}
				}
			}

			sprintf(buffer, "%d", (triColVec[index1][index2] / 4));
			fputs(buffer, colliderFileTriW);

			if (index2 < 3)
			{
				fputs(",", colliderFileTriW);
			}
		}
		fputs("\n", colliderFileTriW);
	}

	printf("done\n");
	fclose(colliderFileTriW);
}

void LvlColliderEditor::draw()
{
	TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}