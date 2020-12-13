#pragma once
#include <iostream>
#include <string>
#include <SDL_mixer.h>
/// <summary>
/// A class that manages the playing, pausing, stopping and manipulation of music and sound effects using the SDL_Mixer library - JP
/// </summary>
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void PlayMusic(std::string& filename, int loops);
	void PlayMusic(Mix_Music* pMusic, int loops);
	void PlaySFX(std::string& filename, int loops, int channel);
	void PlaySFX(Mix_Chunk* pSfx, int loops, int channel);

	void StopMusic(Mix_Music& mus);
	void ClearSound(Mix_Music& mus);

	bool Init();
	void Update(double dt);

private:
	
private:
	static AudioManager* sInstance;



};

