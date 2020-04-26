#include "InventoryButton.h"
#include "HandleEvents.h"

InventoryButton::InventoryButton(Application* app, Vector2D pos, Vector2D scale, Item* ob, CallBackOnClickInventory* call, bool equip, int id)
	: Button(app, nullptr, pos, scale, nullptr, id), object_(ob), equipped(equip){
	callBackInventory_ = call;
	
}

bool InventoryButton::update() {
	HandleEvents* input = HandleEvents::instance();
	Vector2D aux = input->getRealMousePos();
	SDL_Point mouse = { aux.getX(), aux.getY() };
	if (SDL_PointInRect(&mouse, &getDestiny()) && input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		callBackInventory_(app_, this);
		return true;
	}
	else return false;
}


