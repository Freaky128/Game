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
	std::fstream mapFile;
	mapFile.open(path);

	int temp = 0;
	int num = 0;

	for (index = 0; index < 3; index++)
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
	numColliders = num;

	printf("collider num %d\n", numColliders);

	for (index = 0; index < numColliders; index++)
	{
		xpos = Map::GetCoordinates(mapFile, c);
		ypos = Map::GetCoordinates(mapFile, c);
		width = Map::GetCoordinates(mapFile, c);
		height = Map::GetCoordinates(mapFile, c);

		printf("%d\n%d\n%d\n%d\n", xpos, ypos, width, height);

		auto& tcol(manager.addEntity());
		tcol.addComponent<ColliderComponent>("terrain", xpos * mapScale, ypos * mapScale, width * mapScale, height * mapScale);
		tcol.addGroup(GameC::groupColliders);
	}

	mapFile.close();
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
	 char Direc;

	 char c;
	 std::fstream colliderFileTri;
	 colliderFileTri.open(path);

	 colliderFileTri.get(c);
	 numColliders = atoi(&c);
	 colliderFileTri.ignore();

	 for (index = 0; index < numColliders; index++)
	 {
		 colliderFileTri.get(c);
		 Direc = c;
		 colliderFileTri.ignore();

		 printf("%c\n", Direc);
		 
		 Sxpos = Map::GetCoordinates(colliderFileTri, c);
		 Sypos = Map::GetCoordinates(colliderFileTri, c);
		 Fxpos = Map::GetCoordinates(colliderFileTri, c);
		 Fypos = Map::GetCoordinates(colliderFileTri, c);

		 printf("%d\n%d\n%d\n%d\n", Sxpos, Sypos, Fxpos, Fypos);

		 loop = (Fxpos - Sxpos) + 1;

		 if (Direc == 'd')
		 {
			 for (index2 = 0; index2 < loop; index2++)
			 {
				 auto& tcol(manager.addEntity());
				 tcol.addComponent<ColliderComponent>("terrain", (Sxpos + index2) * mapScale, (Sypos + index2) * mapScale, 1 * mapScale, 1 * mapScale);
				 tcol.addGroup(GameC::groupColliders);
			 }
		 }
		 else
		 {
			 for (index2 = 0; index2 < loop; index2++)
			 {
				 auto& tcol(manager.addEntity());
				 tcol.addComponent<ColliderComponent>("terrain", (Sxpos + index2) * mapScale, (Sypos - index2) * mapScale, 1 * mapScale, 1 * mapScale);
				 tcol.addGroup(GameC::groupColliders);
			 }
		 }

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
