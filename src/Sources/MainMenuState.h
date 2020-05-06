#pragma once
#include "GameState.h"

class BeerButton;
class MainMenuState : public GameState
{
private:
	VisualElement* bg_ = nullptr;
	BeerButton* buttonClicked_ = nullptr;
	double button_h= 0;
	double button_w = 0;
	//Diferencia entre los botones en el eje y
	double button_dif = 0;
	bool buttonClick_ = false;	//Para saber si se ha pulsado un boton
protected:
	///<summary>Se inicializa el menu</summary>
	virtual void initState();
	//Para comprobar si existen partidas guardadas
	bool isExistingDataGame();
protected:
	///<summary>crea los 4 botones necesarios del main menu</summary>
	void createButtons();

public:
	MainMenuState(Application* app = nullptr) :GameState(app) { initState(); };
	virtual ~MainMenuState() {};

	//Para decir que se ha pulsado un boton
	void setButtonClick(bool buttonClick, BeerButton* buttonClicked){
		buttonClick_ = buttonClick;
		buttonClicked_ = buttonClicked;
	};
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
};