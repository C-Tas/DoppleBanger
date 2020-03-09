#include "Button.h"
#include "HandleEvents.h"

//Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale)
Button::Button(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack)
	: Draw(texture, &SDL_Rect({ 0,0,0,0 }), pos, scale), ButtonCallBack(callBack) {
	call = 0;
};

Button::Button(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickMenu* callBackMenu)
	: Draw(texture, &SDL_Rect({ 0,0,0,0 }), pos, scale), ButtonCallBackMenu(callBackMenu) {
	call = 1;
};

void Button::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny())) {
		ButtonCallBack();
	}
}

void Button::Render() {
	texture_->render(pos_.getX(),pos_.getY());//provisional
}
