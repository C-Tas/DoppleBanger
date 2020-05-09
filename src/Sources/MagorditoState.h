#pragma once
#include "PlayState.h"
class MagorditoState : public PlayState
{
public:
	MagorditoState(Application* app) : PlayState(app) { initState(); };
	~MagorditoState() {};
private:
	//Dimensiones de las entidades
	const uint W_WIN = app_->getWindowWidth();
	const uint H_WIN = app_->getWindowHeight();

	const uint W_PLAYER = W_WIN / 12;
	const uint H_PLAYER = H_WIN / 6;

	const uint W_MAGORDITO= W_WIN / 8;
	const uint H_MAGORDITO= H_WIN / 4;

	virtual void initState();
};

