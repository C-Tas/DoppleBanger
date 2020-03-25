#pragma once
#include "GameState.h"
#include "Crab.h" //Include temporal
#include "Player.h" //Include temporal
#include "Equipment.h" //Include temporal

class MainMenuState :
	public GameState
{
private:
	Player* player_ = nullptr;
	Crab* crab_ = nullptr;

protected:
	///<summary>Se inicializa el menu</summary>
	void initMenuState();
	///<summary>crea los 4 botones necesarios del main menu</summary>
	void createButtons();

public:
	MainMenuState(Application* app = nullptr) :GameState(app) {initMenuState();};
	virtual ~MainMenuState() {};
	///<summary>Nos lleva al estado controles</summary>
	static void goControlState(Application* app);
	///<summary>Nos lleva al estado creditos</summary>
	static void goCreditsState(Application* app);
	///<summary>Nos lleva al estado load</summary>
	static void goLoadState(Application* app);
	///<summary>Nos lleva al estado Story</summary>
	static void goStoryState(Application* app);
};