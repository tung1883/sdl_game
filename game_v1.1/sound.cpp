#pragma once

#include "Sound.h"

SoundManager* SoundManager::soundInstance = NULL;

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC) {
		Mix_Music* p_music = Mix_LoadMUS(fileName.c_str());

		if (p_music == NULL) {
			std::cout << "Could not load music! Error: " << Mix_GetError() << std::endl;
			return false;
		}
		m_music[id] = p_music;
		return true;
	}
	else if (type == SOUND_SFX) {
		Mix_Chunk* p_sfx = Mix_LoadWAV(fileName.c_str());

		if (p_sfx == NULL) {
			std::cout << "Could not load SFX! Error: " << Mix_GetError() << std::endl;
			return false;
		}
		m_sfxs[id] = p_sfx;
		return true;
	}
	return false;
}

void SoundManager::clear()
{
	Mix_HaltMusic();

	m_music.clear();
	m_sfxs.clear();
}

void SoundManager::fadeClear(int fadeTime) 
{
	Mix_FadeOutMusic(fadeTime);

	m_music.clear();
	m_sfxs.clear();
}

void SoundManager::playMusic(std::string id, int loop) {
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop) {
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}
