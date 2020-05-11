#include "ControlsState.h"

//Calback del bot�n "Volver"
void backToPreviousState(Application* app) {
	app->getGameStateMachine()->popState(); //Vuelve al estado previo
}

void ControlsState::initState() {
	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Controls)); //Textura de los controles
	addRenderUpdateLists(background_);
	//Posici�n y tama�o en funci�n del tama�o de la ventana

	Vector2D scaleButton(app_->getWindowWidth() / 6, app_->getWindowHeight() / 15);
	Vector2D posButton(scaleButton.getX() / 2, scaleButton.getY() / 4);
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), posButton, scaleButton, backToPreviousState, this); //Boton "Volver"

}
