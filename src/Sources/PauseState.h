#pragma once
#include "GameState.h"

//HAY QUE MEJORAR LO DEL BOTON DE MUTE PORQUE SIEMPRE QUE SE CREA EL ESTADO SE CREA EN MUTE_ON
class PauseState : public GameState
{
public:
	PauseState(Application* app = nullptr);
	virtual ~PauseState() {};

	void changeMute(); //Cambia la textura del botón mute

private:
	Button* muteButton = nullptr;

	void initState(); //Inicializa el estado
	#pragma region Callbacks
	static void resume(Application* app);
	static void showControls(Application* app);
	static void goMainMenuState(Application* app);
	static void muteGame(Application* app);
	#pragma endregion
};