#pragma once

#include "ECS.h"
#include "GameC.h"
#include "TextureManager.h"
#include <SDL_ttf.h>

class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, int size, std::string text, const char* font, SDL_Color& colour) : labelText(text), textColour(colour)
	{
		destR.x = xpos;
		destR.y = ypos;
		labelFont = TTF_OpenFont(font, size);

		SetLabelText(labelText);
	}
	~UILabel()
	{
		TTF_CloseFont(labelFont);
	}

	void SetLabelText(std::string labelText)
	{
		labelTexture = TextureManager::LoadFontTexture(labelFont, labelText.c_str(), textColour);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &destR.w, &destR.h);
		srcR.w = destR.w;
		srcR.h = destR.h;
	}

	void draw() override
	{
		TextureManager::Draw(labelTexture, srcR, destR, SDL_FLIP_NONE);
	}

private:
	SDL_Rect destR;
	SDL_Rect srcR = { 0,0,0,0 };
	std::string labelText;
	TTF_Font* labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};