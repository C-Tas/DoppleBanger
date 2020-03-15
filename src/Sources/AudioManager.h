#pragma once
#include <SDL_mixer.h>
#include <string>
#include <map>
using namespace std;

class AudioManager {
public:
	AudioManager();
	AudioManager(int channels);
	~AudioManager();

	bool init();

	//Efectos de sonido
	bool loadSound(int tag, const string& fileName);
	int playChannel(int tag, int loops, int channel);
	void pauseChannel(int channel);
	void resumeChannel(int channel);
	void haltChannel(int channel);
	int setChannelVolume(int volume, int channel);
	int channels();

	//M�sica
	bool loadMusic(int tag, const string& fileName);
	void playMusic(int tag, int loops);
	int setMusicVolume(int volume);
	void haltMusic();
	void pauseMusic();
	void resumeMusic();

private:
	bool initialized_;
	int channels_;
	map<int, Mix_Chunk*> chunks_;
	map<int, Mix_Music*> music_;
};

