#include "AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new AudioManager();

	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

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

void AudioManager::Init()
{
	if (Mix_OpenAudio(44100, /*MIX_DEFAULT_FORMAT*/ AUDIO_S16SYS, 2, 4096) < 0)
	{
		std::cout << "Mixer load failed, error: " << Mix_GetError() << std::endl;
	}

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
	// Mix_PlayChannel(Database->GetMusic(filename), loops);
}
// same as above but plays a sound effect
void AudioManager::PlaySFX(Mix_Chunk* pSfx, int loops, int channel)
{
	Mix_PlayChannel(channel, pSfx, loops);
}
