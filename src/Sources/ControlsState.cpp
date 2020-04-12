#include "ControlsState.h"

//Calback del bot�n "Volver"
void backToPreviousState(Application* app) {
	app->getGameStateMachine()->popState(); //Vuelve al estado previo
}

void ControlsState::initState() {
	controlsImage_ = app_->getTextureManager()->getTexture(Resources::Controls); //Textura de los controles

	//Posici�n y tama�o en funci�n del tama�o de la ventana
	Vector2D scaleButton(app_->getWindowWidth() / 20, app_->getWindowHeight() / 20);
	Vector2D posButton(scaleButton.getX(), scaleButton.getY());
	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), posButton, scaleButton, backToPreviousState); //Bot�n "Volver"
}

//Se redefine el m�todo draw para que renderice los objetos y para que renderice la imagen de los controles
void ControlsState::draw() const
{
	SDL_Rect controlRect;
	controlRect.x = 0; controlRect.y = 0;
	controlRect.w = background; controlRect.h = controlsH;
	controlsImage_->render(controlRect);

	GameState::draw();
}
