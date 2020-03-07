#include "Button.h"
#include "HandleEvents.h"

//Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale)
Button::Button(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack)
	: Draw(nullptr, texture, &SDL_Rect({0,0,0,0}), pos, scale), ButtonCallBack(callBack) {};
	  //Puntero a app nullptr (no necesita (?))

void Button::Logic() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny())) {
		//buttonCallBack(PlayState->getApp())
	}
}

void Button::Render() {
	//Falta la clase texture
}
