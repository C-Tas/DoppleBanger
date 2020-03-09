#pragma once
#include "GameState.h"
#include "Player.h"

class MainMenuState :
	public GameState
{
private:
	//Draw* player_;
public:
	//MainMenuState(Application* app = nullptr) : GameState(app) { printf("MainMenuState"); initMenuState(); };
	MainMenuState(Application* app = nullptr) :GameState(app) {initMenuState();};
	virtual ~MainMenuState() {};
	///<summary>Se inicializa el menu</summary>
	void initMenuState();
	///<summary>crea los 4 botones necesarios del main menu</summary>
	void createButtons();
	static void goControlState(Application* app);
	static void goCreditsState(Application* app);
	static void goLoadState(Application* app);
	static void goStoryState(Application* app);
};