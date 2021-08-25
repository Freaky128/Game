#pragma once
#include <string>
#include "ECS.h"
#include <SDL.h>

class Map
{
public:

	Map();
	//Map(const char* mfp, int ms, int ts);
	~Map(); 

	//void LoadMap(std::string path, int sizeX, int sizeY);
	//void AddTile(int srcX, int srcY, int xpos, int ypos);

	void LoadCollidersRect(const char* path, int mapScale);
	void LoadCollidersTri(const char* path, int mapScale);
	static int GetCoordinates(std::fstream& mapFile, char c);


private:
	//const char* mapFilePath;
	//int mapScale;
	//int tileSize;

};
