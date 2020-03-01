#pragma once
#include "GameState.h"
class SaveLoadState :
	public GameState
{
private:
	bool isLoad_ = false; //TRUE => LOAD //FALSE => SAVE
public:
	SaveLoadState(Application* app, bool load) : GameState(app), isLoad_(load) { if(isLoad_) printf("LoadState"); else printf("SaveState"); };
	void goToGame();
	void goToMainMenu();
};

