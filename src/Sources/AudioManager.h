#pragma once
#include <SDL_mixer.h>
#include "Resources.h"
#include <string>
#include <map>
using namespace std;

enum class MUSIC
{

};

enum class EFFECT : int{
	WALK_DIE = 0,
	PLAYER_ATTACK,
	CLON_IN,
	POTION_MELEE_SKILLS,
	CLON,
	PIMPKIN,
	NPC,
	TUTORIAL,
};

/*canales y sus usos
	canal 0 player walk y morir
	canal 1 para los ataques del player y al invocar clon
	canal 3 para el uso de posiones, melee hit y skills
	canal 4 para el clon
	canal 6 para la calabaza
	canal 7 para la calabaza
*/
class AudioManager {
public:
	AudioManager();
	AudioManager(int channels);
	~AudioManager();

	//<summary>Inicializa la música y los canales, si no puede devuelve 'false'</summary>
	bool initObject();

	//Efectos de sonido
	//<summary>Carga un sonido</summary>
	bool loadSound(int tag, const string& fileName);
	//<summary>Pone música en un canal</summary>
	int playChannel(int tag, int loops, int channel);
	//<summary>Pausa la música de un canal</summary>
	void pauseChannel(int channel);
	//<summary>Reanuda la música de un canal</summary>
	void resumeChannel(int channel);
	//<summary>Para la música de un canal</summary>
	void haltChannel(int channel);
	//<summary>Cambia el volumen de un canal</summary>
	int setChannelVolume(int volume, int channel);
	//<summary>Devuelve el total de canales</summary>
	int channels();

	//Música
	//<summary>Carga música</summary>
	bool loadMusic(int tag, const string& fileName);
	//<summary>Pone música</summary>
	void playMusic(int tag, int loops);
	//<summary>Cambia el volumen de la música</summary>
	int setMusicVolume(int volume);
	//<summary>Para la música</summary>
	void haltMusic();
	//<summary>Pausa la música</summary>
	void pauseMusic();
	//<summary>Reanuda la música</summary>
	void resumeMusic();

private:
	bool initialized_;
	int channels_;
	map<int, Mix_Chunk*> chunks_;
	map<int, Mix_Music*> music_;
};

