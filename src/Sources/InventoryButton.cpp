#include "InventoryButton.h"
#include "HandleEvents.h"

InventoryButton::InventoryButton(Application* app, GameState* state, Texture* texture, Vector2D pos, Vector2D scale, Item* ob, CallBackOnClickInventory* call, int id)
	: Button(app,state, texture, pos, scale, nullptr, id), object_(ob){
	callBackInventory_ = call;
}

bool InventoryButton::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getRealMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		callBackInventory_(currentState_, this);
		return true;
	}
	else return false;
}

