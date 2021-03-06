#include "Map.h"
#include "gameC.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"

extern Manager manager;

Map::Map() {}

/*Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts)
{
	
}*/

Map::~Map()
{
	
}

/*void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) 
	{
		for (int x = 0; x < sizeX; x++) 
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * (tileSize * mapScale), y * (tileSize * mapScale));
			mapFile.ignore();
		}
	}

	mapFile.ignore();
	
	for (int y = 0; y < sizeY; y++) 
	{
		for (int x = 0; y < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * (tileSize * mapScale), y * (tileSize * mapScale), tileSize * mapScale);
				tcol.addGroup(GameC::groupColliders);
			}
			mapFile.ignore();
		}
	}
	
	mapFile.close();
}*/

/*void Map::AddTile(int srcX, int srcY, int xpos, int ypos) 
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(GameC::groupMap);
}*/

 void Map::LoadCollidersRect(const char* path, int mapScale)
{

	int numColliders;
	int xpos = 0;
	int ypos = 0;
	int width = 0;
	int height = 0;
	int index;

	char c;
	std::fstream colliderFileRect;
	colliderFileRect.open(path);

	int temp = 0;
	int num = 0;

	for (index = 0; index < 3; index++)
	{
		colliderFileRect.get(c);
		temp = atoi(&c);

		if ((index != 0) && (num != 0))
		{
			num = num * 10;
		}
		num += temp;
	}
	colliderFileRect.ignore();
	numColliders = num;

	printf("collider num %d\n", numColliders);

	for (index = 0; index < numColliders; index++)
	{
		xpos = Map::GetCoordinates(colliderFileRect, c);
		ypos = Map::GetCoordinates(colliderFileRect, c);
		width = Map::GetCoordinates(colliderFileRect, c);
		height = Map::GetCoordinates(colliderFileRect, c);

		printf("x: %d\ny: %d\nw: %d\nh: %d\n", xpos, ypos, width, height);

		auto& tcol(manager.addEntity());
		tcol.addComponent<ColliderComponent>("terrain", xpos * mapScale, ypos * mapScale, width * mapScale, height * mapScale);
		tcol.addGroup(GameC::groupColliders);
	}

	colliderFileRect.close();
}

 void Map::LoadCollidersTri(const char* path, int mapScale)
 {

	 int numColliders;
	 int Sxpos = 0;
	 int Sypos = 0;
	 int Fxpos = 0;
	 int Fypos = 0;
	 int index;
	 int index2;
	 int loop = 0;
	 char direc;

	 char c;
	 std::fstream colliderFileTri;
	 colliderFileTri.open(path);

	 int temp = 0;
	 int num = 0;

	 for (index = 0; index < 3; index++)
	 {
		 colliderFileTri.get(c);
		 temp = atoi(&c);

		 if ((index != 0) && (num != 0))
		 {
			 num = num * 10;
		 }
		 num += temp;
	 }
	 colliderFileTri.ignore();
	 numColliders = num;

	 printf("num of colliders: %d\n", numColliders);

	 for (index = 0; index < numColliders; index++)
	 {
		 colliderFileTri.get(c);
		 direc = c;
		 colliderFileTri.ignore();

		 printf("collider direction: %c\n", direc);
		 
		 Sxpos = Map::GetCoordinates(colliderFileTri, c);
		 Sypos = Map::GetCoordinates(colliderFileTri, c);
		 Fxpos = Map::GetCoordinates(colliderFileTri, c);
		 Fypos = Map::GetCoordinates(colliderFileTri, c);

		 printf("Sx: %d\nSy: %d\nFx: %d\nFy: %d\n", Sxpos, Sypos, Fxpos, Fypos);

		auto& tcol(manager.addEntity());
		tcol.addComponent<ColliderComponentTri>(direc, Sxpos * mapScale, Sypos * mapScale, Fxpos * mapScale, Fypos * mapScale, mapScale);
		tcol.addGroup(GameC::groupTriColliders);
	 }
	 colliderFileTri.close();
 }

 int Map::GetCoordinates(std::fstream& mapFile, char c)
{
	int temp = 0;
	int num = 0;
	int index;

	for (index = 0; index < 4; index++)
	{
		mapFile.get(c);
		temp = atoi(&c);

		if ((index != 0) && (num != 0))
		{
			num = num * 10;
		}
		num += temp;
	}
	mapFile.ignore();
	return num;
}
