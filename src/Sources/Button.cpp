#include "Button.h"
#include "HandleEvents.h"

//Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale)
Button::Button(Application* app,Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack)
	: Draw(app,texture, SDL_Rect({(int)pos.getX(),(int)pos.getY(),(int)scale.getX(),(int)scale.getY()}), pos, scale), ButtonCallBack(callBack){};

bool Button::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	
	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		ButtonCallBack(app_);
		return true;
	}
	else return false;

}

const void Button::draw()  {
	//Falta la clase texture
	texture_->render(destiny_, SDL_FLIP_NONE);
}
