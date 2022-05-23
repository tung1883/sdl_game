#pragma once

#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"

TextureManager* TextureManager::managerInstance = NULL;

bool TextureManager::loadTexture(const char* filepath, std::string textureID, SDL_Renderer* m_renderer, int r, int g, int b) {
	SDL_Surface* tempSurface = NULL;
	tempSurface = IMG_Load(filepath);
	if (tempSurface == NULL) {
		std::cout << "Can not load surface for " << textureID <<"!The SDL Error : " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		if (SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 255, 0)) != 0)
		{
			std::cout << "Unable to set color key" << std::endl;
		};
		SDL_Texture* texture = NULL;
		texture = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
		if (texture == NULL) {
			std::cout << "Can not load " << textureID <<" texture!The SDL Error : " << SDL_GetError() << std::endl;
			return false;
		}
		else {
			textureMap[textureID] = texture;
			return true;
		}
	}
}

void TextureManager::draw(std::string textureID, float x, float y, int width, int height, SDL_Renderer* m_renderer, SDL_RendererFlip textureFlip) {
	SDL_Rect srcRect, destRect;
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;

	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopyEx(m_renderer, textureMap[textureID], &srcRect, &destRect, 0, 0, textureFlip);
}

void TextureManager::drawFrame(std::string textureID, float x, float y, int width, int height, int currentFrame, int currentRow, 
	SDL_Renderer* m_renderer, double angle, int alpha, SDL_RendererFlip textureFlip) {
	SDL_Rect srcRect, destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow-1);
	srcRect.w = width;
	srcRect.h = height;

	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_SetTextureAlphaMod(textureMap[textureID], alpha);
	SDL_RenderCopyEx(m_renderer, textureMap[textureID], &srcRect, &destRect, angle, 0, textureFlip);
} 

//TheTextureManager::Instance()->drawTile(ts.Name, ts.margin, ts.spacing,
//	(j* m_TileSize) - x2, (i* m_TileSize) - y2, m_TileSize, m_TileSize,
//	tileRow, tileCol, TheGame::Instance()->getRenderer());

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height,
	int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
	SDL_Rect src, dest;
	src.x = margin + (spacing + width) * currentFrame;
	src.y = margin + (spacing + height) * currentRow;
	src.w = dest.w = width;
	src.h = dest.h = height;
	dest.x = x;
	dest.y = y;
	SDL_RenderCopyEx(pRenderer, textureMap[id], &src, &dest, 0, 0, SDL_FLIP_NONE);
};

void TextureManager::clearTextureFromMap(std::string textureID)
{
	textureMap.erase(textureID);
};