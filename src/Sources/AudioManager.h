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

	//<summary>Inicializa la m�sica y los canales, si no puede devuelve 'false'</summary>
	bool init();

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
	//<summary>Estadisticas del jugador</summary>
	int channels();

	//M�sica
	//<summary>Carga m�sica</summary>
	bool loadMusic(int tag, const string& fileName);
	//<summary>Pone m�sica</summary>
	void playMusic(int tag, int loops);
	//<summary>Cambia el volumen de la m�sica</summary>
	int setMusicVolume(int volume);
	//<summary>Para la m�sica</summary>
	void haltMusic();
	//<summary>Pausa la m�sica</summary>
	void pauseMusic();
	//<summary>Reanuda la m�sica</summary>
	void resumeMusic();

private:
	bool initialized_;
	int channels_;
	map<int, Mix_Chunk*> chunks_;
	map<int, Mix_Music*> music_;
};

