#include "Button.h"
#include "HandleEvents.h"


Button::Button(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack) : Draw(texture,pos,scale), ButtonCallBack(callBack) {};

void Button::logic() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestRect())) {
		//buttonCallBack(PlayState->getApp())
	}
}

void Button::render() {
	//Falta la clase texture
}
