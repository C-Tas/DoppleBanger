#include "InventoryButton.h"
#include "HandleEvents.h"

InventoryButton::InventoryButton(GameState* state, Texture* texture, Vector2D pos, Vector2D scale, Equipable* ob, CallBackOnClickInventory* call)
	: Button(state, texture, pos, scale, nullptr), object_(ob){
	callBackInventory_ = call;
}

void InventoryButton::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny())) {
		callBackInventory_(currentState_,object_);
}