#include "Button.h"
#include "HandleEvents.h"

//Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale)
Button::Button(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack)
	: Draw(texture, &SDL_Rect({int(pos.getX()),int(pos.getY()),int(scale.getX()),int(scale.getY())}), pos, scale), ButtonCallBack(callBack) {};

void Button::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() }; 
//#ifdef _DEBUG
//	if (input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT));
//	cout << input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT) << endl;
//#endif
	if (SDL_PointInRect(&mouse, &getDestiny())&&input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
#ifdef _DEBUG
		cout << "he clickeado un boton" << endl;
#endif
		ButtonCallBack;
#ifdef _DEBUG
		cout << "he ejecutado el callBack" << endl;
#endif
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
