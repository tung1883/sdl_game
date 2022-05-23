#pragma once

#include <iostream>
#include "map"
#include <SDL_mixer.h>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	static SoundManager* Instance() {
		if (soundInstance == NULL) {
			soundInstance = new SoundManager();
		}
		return soundInstance;
	};

	bool load(std::string fileName, std::string id, sound_type type);

	void playSound(std::string, int loop);
	void playMusic(std::string, int loop);

	void clear();
	void fadeClear(int fadeTime);

private:
	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&);
	SoundManager& operator = (const SoundManager&);

	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;

	static SoundManager* soundInstance;
};

typedef SoundManager TheSoundManager;