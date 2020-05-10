#pragma once
#include "PlayState.h"
class MagorditoState : public PlayState
{
public:
	MagorditoState(Application* app) : PlayState(app) { initState(); };
	~MagorditoState() {};
private:
	//Dimensiones de las entidades
	const double W_WIN = app_->getWindowWidth();
	const double H_WIN = app_->getWindowHeight();

	const double W_PLAYER = W_WIN / 12;
	const double H_PLAYER = H_WIN / 6;

	const double W_MAGORDITO= W_WIN / 8;
	const double H_MAGORDITO= H_WIN / 4;

	const double W_H_ALTAR= W_WIN / 8;
	Vector2D scaleAltar = Vector2D(W_H_ALTAR, W_H_ALTAR);

	virtual void initState();
};

