#include "AudioManager.h"




AudioManager::AudioManager()
{
	// Get the database or import manager instance, this will depend on our implementation
}

AudioManager::~AudioManager()
{
	// null the import manager once i have it
	Mix_Quit(); // Close the audio

}

void AudioManager::StopMusic(Mix_Music& mus)
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::ClearSound(Mix_Music& mus)
{
}

bool AudioManager::Init()
{
	if (this == nullptr)
	{
		return false;
	}

	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) < 0)
	{
		std::cout << "Mixer load failed, error: " << Mix_GetError() << std::endl;
	}

	return true;

}

void AudioManager::Update(double dt)
{
}

void AudioManager::PlayMusic(std::string& filename, int loops)
{
	// Mix_PlayMusic(Database->GetMusic(filename), loops);
}

void AudioManager::PlayMusic(Mix_Music* pMusic, int loops) // overload for testing until the database and import manager classes are created
{
	Mix_VolumeMusic(10);
	Mix_PlayMusic(pMusic, loops);
}
void AudioManager::PlaySFX(std::string& filename, int loops, int channel)
{
	// Mix_PlayChannel(Database->GetSFX(filename), loops);
}
// same as above but plays a sound effect
void AudioManager::PlaySFX(Mix_Chunk* pSfx, int loops, int channel)
{
	Mix_PlayChannel(channel, pSfx, loops);
}
