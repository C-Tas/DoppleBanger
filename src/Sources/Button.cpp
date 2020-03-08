#include "Button.h"
#include "HandleEvents.h"

//Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale)
Button::Button(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack)
	: Draw(texture, &SDL_Rect({0,0,0,0}), pos, scale), ButtonCallBack(callBack) {};

void Button::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny())) {
		//buttonCallBack(PlayState->getApp())
	}
}

const void Button::draw() {
	//Falta la clase texture
	SDL_Rect dest;
	dest.x=pos_.getX();
	dest.y=pos_.getY();
	dest.w=scale_.getX();
	dest.h=scale_.getY();
	texture_->render(dest);
}
