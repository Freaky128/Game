#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	void addTexture(std::string id, const char* path);
	SDL_Texture* getTexture(std::string id);

private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;

};