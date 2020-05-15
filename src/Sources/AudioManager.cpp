#include "AudioManager.h"
#include <iostream>
#include <assert.h>
using namespace std;

AudioManager::AudioManager() : AudioManager(8) {}

AudioManager::AudioManager(int channels) : initialized_(false), channels_(channels) {}

AudioManager::~AudioManager() {
	if (!initialized_) return;

	//Libera los map de la clase
	for (const auto& pair : chunks_) {
		if (pair.second != nullptr) Mix_FreeChunk(pair.second);
	}

	for (const auto& pair : music_) {
		if (pair.second != nullptr) Mix_FreeMusic(pair.second);
	}

	Mix_Quit();
}

bool AudioManager::initObject() {
	if (initialized_)
		return false;

	// open the mixer
	int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	assert(mixOpenAudio == 0);

	// initialize supported formats
	int mixInit_ret = Mix_Init(
		MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	assert(mixInit_ret != 0);

	// set number of channels
	channels_ = Mix_AllocateChannels(channels_);

	//Inicializa el volumen de todos los canales y la musica
	for (int i = 0; i < Resources::NumSoundChannels; i++) {
		setChannelVolume(Resources::audioVolume.at(i).volume, i);
	}

	initialized_ = true;

	return true;
}

bool AudioManager::loadSound(int tag, const string& fileName) {
	if (!initialized_)
		return false;

	Mix_Chunk* chunk = Mix_LoadWAV(fileName.c_str());
	if (chunk != nullptr) {
		Mix_Chunk* curr = chunks_[tag];
		if (curr != nullptr)
			Mix_FreeChunk(curr);
		chunks_[tag] = chunk;
		return true;
	}
	else {
		throw "Couldn't load sound file: " + fileName;
		return false;
	}
}

int AudioManager::playChannel(int tag, int loops, int channel) {
	Mix_Chunk* chunk = chunks_[tag];
	if (chunk != nullptr) {
		return Mix_PlayChannel(channel, chunk, loops);
	}
	else {
		return -1;
	}
}

void AudioManager::pauseChannel(int channel) {
	Mix_Pause(channel);
}

void AudioManager::resumeChannel(int channel) {
	Mix_Resume(channel);
}

void AudioManager::haltChannel(int channel) {
	Mix_HaltChannel(channel);
}

int AudioManager::setChannelVolume(int volume, int channel) {
	return Mix_Volume(channel, volume);
}

int AudioManager::channels() {
	return channels_;
}

void AudioManager::setAllSoundVolumen()
{
	if (muteSounds_) {
		for (int i = Resources::NumMusicChannels; i < Resources::NumSoundChannels; i++) {
			setChannelVolume(0, i);
		}
	}
	else {
		for (int i = Resources::NumMusicChannels; i < Resources::NumSoundChannels; i++) {
			setChannelVolume(Resources::audioVolume.at(i).volume, i);
		}
	}
}

void AudioManager::setAllMusicVolumen()
{
	if (muteMusic_) {
		for (int i = 0; i < Resources::NumMusicChannels; i++) {
			setChannelVolume(0, i);
		}
	}
	else {
		for (int i = 0; i < Resources::NumMusicChannels; i++) {
			setChannelVolume(Resources::audioVolume.at(i).volume, i);
		}
	}
}
