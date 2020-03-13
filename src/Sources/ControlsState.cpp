#include "ControlsState.h"

void ControlsState::backToPreviousState() {
	app_->getStateMachine()->popState();
}

void ControlsState::initState() {
	controlsImage_ = app_->getTextureManager()->getTexture(Resources::Controls);
}
//Se redefine el método draw para que renderice los objetos y para que renderice la imagen de los controles
void ControlsState::draw() const
{
	GameState::draw();

	SDL_Rect controlRect;
	controlRect.x = 0; controlRect.y = 0;
	controlRect.w = controlsW; controlRect.h = controlsH;
	controlsImage_->render(controlRect);
}
