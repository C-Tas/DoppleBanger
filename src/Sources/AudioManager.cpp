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

bool AudioManager::loadMusic(int tag, const string& fileName) {
	if (!initialized_)
		return false;

	Mix_Music* music = Mix_LoadMUS(fileName.c_str());
	if (music != nullptr) {
		Mix_Music* curr = music_[tag];
		if (curr != nullptr)
			Mix_FreeMusic(curr);
		music_[tag] = music;
		return true;
	}
	else {
		throw "Couldn't load music file: " + fileName;
		return false;
	}
}

void AudioManager::playMusic(int tag, int loops = -1) {
	Mix_Music* music = music_[tag];
	if (music != nullptr) {
		Mix_PlayMusic(music, loops);
	}
}

int AudioManager::setMusicVolume(int volume) {
	return Mix_VolumeMusic(volume);
}

void AudioManager::haltMusic() {
	Mix_HaltMusic();
}

void AudioManager::pauseMusic() {
	Mix_PauseMusic();
}

void AudioManager::resumeMusic() {
	Mix_ResumeMusic();
}