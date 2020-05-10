#pragma once
#include "Draw.h"
class Kirin : public Draw
{
public:
	Kirin(Application* app, Vector2D pos, Vector2D scale);
	~Kirin() {};

	virtual bool update();

private:
	const int NUM_FRAMES = 13;		//Numero de frames de la animaciones
	const int W_H_FRAME = 100;		//Tamaño del frame en el spriteheet
	const int FRAME_RATE = 100;		//Velocidad
	const int FRAME_ACTION = 7;		//Frame en el que hara daño
	const double KIRIN_DMG = 0;	//Daño que se va a infligir
	bool attacked_ = false;			//Para infligir daño una sola vez
	virtual void initObject();
};

