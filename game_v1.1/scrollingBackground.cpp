#pragma once

#include "Game.h"
#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground(const ObjectParams* params, int scrollSpeed) 
	:GameObject(params)
{
	m_scrollSpeed = scrollSpeed;
	
	m_srcRect1.x = 0;
	m_srcRect1.y = 0;
	m_destRect1.x = m_position.getX();
	m_destRect1.y = m_position.getY();
	
	m_srcRect1.w = m_destRect1.w = m_srcRect1Width = m_destRect1Width = m_width;
	m_srcRect1.h = m_destRect1.h = m_height;
	
	m_srcRect2.x = 0;
	m_destRect2.x = m_position.getX() + m_width;
	m_srcRect2.y = 0;
	m_destRect2.y = m_position.getY();
	
	m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
	m_srcRect2.h = m_destRect2.h = m_height;
	
	count = 0;
	maxCount = 1;
}

void ScrollingBackground::draw()
{
	//TheTextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height,
	//	m_currentFrame, m_currentRow, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_NONE);
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),
		TheTextureManager::Instance()->getTextureMap()[m_textureID],
		&m_srcRect1, &m_destRect1, 0, 0, SDL_FLIP_NONE);
	
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),
		TheTextureManager::Instance()->getTextureMap()[m_textureID],
		&m_srcRect2, &m_destRect2, 0, 0, SDL_FLIP_NONE);
}

void ScrollingBackground::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));

	if (count == maxCount) {
		m_srcRect1.x += m_scrollSpeed;
		m_srcRect1.w -= m_scrollSpeed;
		m_destRect1.w -= m_scrollSpeed;
	
		m_srcRect2.w += m_scrollSpeed;
		m_destRect2.w += m_scrollSpeed;
		m_destRect2.x -= m_scrollSpeed;
	
		if (m_destRect2.w >= m_width) {
			m_srcRect1.x = 0;
			m_srcRect1.y = 0;
			m_destRect1.x = m_position.getX();
			m_destRect1.y = m_position.getY();
	
			m_srcRect1.w = m_destRect1.w = m_srcRect1Width = m_destRect1Width = m_width;
			m_srcRect1.h = m_destRect1.h = m_height;
	
			m_srcRect2.x = 0;
			m_destRect2.x = m_position.getX() + m_width;
			m_srcRect2.y = 0;
			m_destRect2.y = m_position.getY();
	
			m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
			m_srcRect2.h = m_destRect2.h = m_height;
		}
		count = 0;
	}
	count++;
}

void ScrollingBackground::clean()
{
	GameObject::clean();
}