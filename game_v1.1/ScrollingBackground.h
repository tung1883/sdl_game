#pragma once

#include "GameObject.h"

class ScrollingBackground : public GameObject
{
public:
	ScrollingBackground(const ObjectParams* params, int scrollSpeed);
	~ScrollingBackground();

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_scrollSpeed;
	
	int count;
	int maxCount;
	
    SDL_Rect m_srcRect1;
    SDL_Rect m_srcRect2;
	
    SDL_Rect m_destRect1;
    SDL_Rect m_destRect2;
	
    int m_srcRect1Width;
    int m_srcRect2Width;
	
    int m_destRect1Width;
    int m_destRect2Width;
};