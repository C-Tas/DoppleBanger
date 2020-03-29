#pragma once
#include "GameState.h"
class SaveLoadState :
	public GameState
{
public:
	SaveLoadState(Application* app, bool load) :
		GameState(app), isLoad_(load) {
		if (isLoad_) printf("LoadState");
		else printf("SaveState");
		initState();
	};
	virtual ~SaveLoadState() {};
	void goToGame();
	void goToMainMenu();

private:
	void initState();
	bool isLoad_ = false; //TRUE => LOAD //FALSE => SAVE
};

