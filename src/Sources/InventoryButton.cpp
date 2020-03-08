#include "InventoryButton.h"
#include "HandleEvents.h"

InventoryButton::InventoryButton(Texture* texture, Vector2D pos, Vector2D scale, Equipable* ob, CallBackOnClick* callBack): Button(texture,pos,scale,callBack),object_(ob){
}
void InventoryButton::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny())) {
		ButtonCallBack(this);
	}
}