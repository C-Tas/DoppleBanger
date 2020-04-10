#pragma once
#include "GameState.h"
#include "Crab.h" //Include temporal
#include "Player.h" //Include temporal
#include "Equipment.h" //Include temporal

class MainMenuState : public GameState
{
private:
	Draw* bg_ = nullptr;
	double button_h= 0;
	double button_w = 0;
	//Diferencia entre los botones en el eje y
	double button_dif = 0;
	Player* player_ = nullptr;
	//Crab* crab_ = nullptr;

protected:
	///<summary>Se inicializa el menu</summary>
	virtual void initState();
	///<summary>crea los 4 botones necesarios del main menu</summary>
	void createButtons();

public:
	MainMenuState(Application* app = nullptr) :GameState(app) { initState(); };
	virtual ~MainMenuState() {};
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