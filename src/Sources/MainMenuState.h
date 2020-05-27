#pragma once
#include "GameState.h"

class BeerButton;
class MainMenuState : public GameState
{

public:
	MainMenuState(Application* app = nullptr) :GameState(app) { initState(); };
	virtual ~MainMenuState() {};

	//Para decir que se ha pulsado un boton
	void setButtonClick(bool buttonClick, BeerButton* buttonClicked) {
		buttonClick_ = buttonClick;
		buttonClicked_ = buttonClicked;
	};

private:
	//Botones de mute
	Button* muteMusicButton = nullptr;
	Button* muteSoundButton = nullptr;
	//Fondo
	VisualElement* bg_ = nullptr;
	//Botones principales
	BeerButton* buttonClicked_ = nullptr;
	double button_h = 0;
	double button_w = 0;
	//Diferencia entre los botones en el eje y
	double button_dif = 0;
	bool buttonClick_ = false;	//Para saber si se ha pulsado un boton

	///<summary>Se inicializa el menu</summary>
	virtual void initState();
	//Para comprobar si existen partidas guardadas
	bool isExistingDataGame();
	///<summary>crea los 4 botones necesarios del main menu</summary>
	void createButtons();

	void changeMuteSound(); //Cambia la textura del botón muteMusic
	void changeMuteMusic();	//Cambia la textura del botón muteSound
#pragma region Callbacks
///<summary>Nos lleva al estado controles</summary>
	static void goControlState(Application* app);
	///<summary>Nos lleva al estado creditos</summary>
	static void goCreditsState(Application* app);
	///<summary>Nos lleva al estado load</summary>
	static void goLoadState(Application* app);
	///<summary>Nos lleva al estado Story</summary>
	static void goStoryState(Application* app);
	//Para salir del juego
	static void exitGame(Application* app);
	//Silencia/Habilita efectos de sonido
	static void muteSounds(Application* app);
	//Silencia/Habili
	static void muteMusic(Application* app);
#pragma endregion
};