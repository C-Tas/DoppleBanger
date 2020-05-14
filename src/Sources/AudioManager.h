#pragma once
#include <SDL_mixer.h>
#include "Resources.h"
#include <string>
#include <map>
using namespace std;


class AudioManager {
public:
	AudioManager();
	AudioManager(int channels);
	~AudioManager();

	//<summary>Inicializa la m�sica y los canales, si no puede devuelve 'false'</summary>
	bool initObject();

	//Efectos de sonido
	//<summary>Carga un sonido</summary>
	bool loadSound(int tag, const string& fileName);
	//<summary>Pone m�sica en un canal</summary>
	int playChannel(int tag, int loops, int channel);
	//<summary>Pausa la m�sica de un canal</summary>
	void pauseChannel(int channel);
	//<summary>Reanuda la m�sica de un canal</summary>
	void resumeChannel(int channel);
	//<summary>Para la m�sica de un canal</summary>
	void haltChannel(int channel);
	//<summary>Cambia el volumen de un canal</summary>
	int setChannelVolume(int volume, int channel);
	//<summary>Devuelve el total de canales</summary>
	int channels();

	//Mute
	bool getMuteSounds() { return muteSounds_; };
	inline void setMuteSounds() { muteSounds_ = !muteSounds_; };
	void setAllSoundVolumen();

	bool getMuteMusic() { return muteMusic_; };
	inline void setMuteMusic() { muteMusic_ = !muteMusic_; };
	void setAllMusicVolumen();
private:
	bool initialized_;
	bool muteMusic_ = false;	//Musica
	bool muteSounds_ = false;	//Efectos de sonido
	int channels_;
	map<int, Mix_Chunk*> chunks_;
	map<int, Mix_Music*> music_;
};

