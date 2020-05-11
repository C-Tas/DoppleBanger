#pragma once
#include "GameState.h"

class PauseState : public GameState
{
public:
	PauseState(Application* app = nullptr);
	virtual ~PauseState() {};


private:
	Button* muteMusicButton = nullptr;
	Button* muteSoundButton = nullptr;

	void initState(); //Inicializa el estado
	void changeMuteSound(); //Cambia la textura del botón muteMusic
	void changeMuteMusic();	//Cambia la textura del botón muteSound

	#pragma region Callbacks
	static void resume(Application* app);
	static void showControls(Application* app);
	static void goMainMenuState(Application* app);
	static void muteSounds(Application* app);
	static void muteMusic(Application* app);
	#pragma endregion
};