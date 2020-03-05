#pragma once
#include "GameState.h"
class MainMenuState :
	public GameState
{
private:
public:
	//MainMenuState(Application* app = nullptr) : GameState(app) { printf("MainMenuState"); initMenuState(); };
	MainMenuState(Application* app = nullptr) : GameState(app) ;
	virtual ~MainMenuState() {};
	void initMenuState();
	void goControlState();
	void goCreditsState();
	void goLoadState();
	void goStoryState();
};