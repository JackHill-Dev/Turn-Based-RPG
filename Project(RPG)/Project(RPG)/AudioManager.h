#pragma once
#include <iostream>
#include <string>
#include <SDL_mixer.h>
/// <summary>

/// </summary>
class AudioManager
{
public:
	static AudioManager* Instance();
	static void Release();

	void PlayMusic(std::string& filename, int loops);
	void PlayMusic(Mix_Music* pMusic, int loops);
	void PlaySFX(std::string& filename, int loops, int channel);
	void PlaySFX(Mix_Chunk* pSfx, int loops, int channel);

	void StopMusic(Mix_Music& mus);
	void ClearSound(Mix_Music& mus);

	void Init();
	void Update(double dt);

private:
	AudioManager();
	~AudioManager();
private:
	static AudioManager* sInstance;



};

