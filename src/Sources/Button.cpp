#include "Button.h"
#include "HandleEvents.h"

bool Button::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos(); //Guardas la posicion del raton
	SDL_Point mouse = { aux.getX(), aux.getY() };
	
	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		cbClick_(app_); //Se llama al CallBack
		return true;
	}
	else return false;
}

const void Button::draw()  {
	texture_->render(destiny_, SDL_FLIP_NONE);
}
