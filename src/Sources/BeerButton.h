#pragma once
#include "Button.h"

class GameState;

class BeerButton : public Button
{
public:
	BeerButton(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* cb);
	~BeerButton() {};

	virtual bool update();
	const virtual void draw();
private:
	Texture* buttonTx_ = nullptr;		//Textura del boton
	bool clicked_ = false;				//Para saber cuando se renderiza la animacion
	bool select_ = false;				//Para sabber si el raton esta encima del boton
	Anim beerAnim{ 0, 0, 0, 0, false };	//Animacion de las cervezas
	const int NUM_FRAMES = 6;			//Frames totales
	const int W_FRAME = 675;			//Ancho del frame
	const int H_FRAME = 375;			//Alto del frame
	const int FRAME_RATE = 100;			//Velocidad por frame (milisegundos)
	SDL_Rect beerRect{ 0, 0, 0, 0 };	//Rectangulo de las cervezas

	//Inicializa la animacion
	virtual void initAnims();
	//Resetea el boton al cambiar de estado
	void resetButton();
};