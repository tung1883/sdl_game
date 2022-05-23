#pragma once
#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager {
public:
	static TextureManager* Instance() {
		if (managerInstance == NULL) {
			managerInstance = new TextureManager();
		}
		return managerInstance;
	}

	bool loadTexture(const char* filepath, std::string textureID, SDL_Renderer* gameRenderer, int r = 0, int g = 0, int b = 0);
	void draw(std::string textureID, float x, float y, int width, int height, SDL_Renderer* gameRenderer, 
		SDL_RendererFlip textureFlip = SDL_FLIP_NONE);
	void drawFrame(std::string textureID, float x, float y, int width, int height, int currentFrame, int currentRow, 
		SDL_Renderer* gameRenderer, double angle, int alpha, SDL_RendererFlip textureFlip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height,
		int currentRow, int currentFrame, SDL_Renderer* pRenderer );
	void clearTextureFromMap(std:: string textureID);

	std::map<std::string, SDL_Texture*> getTextureMap() {
		return textureMap;
	}

private:
	TextureManager() {};
	~TextureManager() {};

	std::map<std::string, SDL_Texture*> textureMap;

	static TextureManager* managerInstance;
};

typedef TextureManager TheTextureManager;