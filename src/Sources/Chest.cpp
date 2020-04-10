#include "Chest.h"
#include "HandleEvents.h"

void Chest::pick() {

}

bool Chest::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos(); //Guardas la posicion del raton
	SDL_Point mouse = { aux.getX(), aux.getY() };

	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		pick();
		return true;
	}
	else return false;
}