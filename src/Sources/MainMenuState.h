#pragma once
#include "GameState.h"
#include "Player.h"

class MainMenuState :
	public GameState
{
private:
	//Draw* player_;
		///<summary>Se inicializa el menu</summary>
	void initMenuState();
	///<summary>crea los 4 botones necesarios del main menu</summary>
	void createButtons();
	///<summary>Nos lleva al estado controles</summary>
	static void goControlState(Application* app);
	///<summary>Nos lleva al estado creditos</summary>
	static void goCreditsState(Application* app);
	///<summary>Nos lleva al estado load</summary>
	static void goLoadState(Application* app);
	///<summary>Nos lleva al estado Story</summary>
	static void goStoryState(Application* app);
public:
	//MainMenuState(Application* app = nullptr) : GameState(app) { printf("MainMenuState"); initMenuState(); };
	MainMenuState(Application* app = nullptr) :GameState(app) {initMenuState();};
	virtual ~MainMenuState() {};

};