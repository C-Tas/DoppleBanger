#include "ControlsState.h"

//Calback del botón "Volver"
void backToPreviousState(Application* app) {
	app->getStateMachine()->popState(); //Vuelve al estado previo
}

void ControlsState::initState() {
	controlsImage_ = app_->getTextureManager()->getTexture(Resources::Controls); //Textura de los controles

	//Posición y tamaño en función del tamaño de la ventana
	Vector2D scaleButton(app_->getWindowWidth() / 20, app_->getWindowHeight() / 20);
	Vector2D posButton(scaleButton.getX(), scaleButton.getY());
	createButton(app_->getTextureManager()->getTexture(Resources::BackButton), posButton, scaleButton, backToPreviousState, app_); //Botón "Volver"
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