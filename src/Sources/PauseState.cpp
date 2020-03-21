#include "PauseState.h"
#include "ControlsState.h"
#include "GameManager.h"

#pragma region CallBacks
///<summary>Reanuda la partida actual</summary>
void resume(Application* app) {
	app->getStateMachine()->popState();
}

///<summary>Muestra los controles</summary>
void showControls(Application* app) {
	app->getStateMachine()->pushState(new ControlsState(app));
}

///<summary>Vuelve al menú principal sin guardar partida</summary>
void goMainMenuState(Application* app) {
	app->getStateMachine()->clearAllStateExceptFirst();
}

///<summary>
/// Silencia/Habilita el sonido
/// Nota: Los efectos de sonido viajan a través de diversos canales y no se pueden silenciar. Los canales funcionan
/// de tal manera que al darle playChannel(...) con loop = 0 estos se activan. Por ello, la forma de que los efectos de sonido no suenen
/// es que se controlen en los sitios en los que se efectúan. En caso de que la música vaya a sonar por canales habrá que hacer los respectivos cambios.
///</summary>
void muteGame(Application* app) {
	if (app->getMute()) app->getAudioManager()->resumeMusic(); //Reanuda la música
	else app->getAudioManager()->pauseMusic(); //Pausa la música

	app->setMute(); //Cambia el booleano que controla el mute
	static_cast<PauseState*>(app->getGameStateMachine()->getState())->changeMute(); //Cambia la textura del botón mute del PauseState
}
#pragma endregion

PauseState::PauseState(Application* app) : GameState(app) {
	initState();
}

void PauseState::changeMute()
{
}

void PauseState::initState()
{
	//Creación de botones
	Vector2D sizeButton(app_->getWindowWidth() / 6, app_->getWindowHeight() / 10);
	Vector2D posButton(app_->getWindowWidth() / 2 - sizeButton.getX() / 2, app_->getWindowHeight() / 4 - sizeButton.getY() / 2);

	//Botón de reanudar
	createButton(app_->getTextureManager()->getTexture(Resources::Resume), posButton, sizeButton, resume, app_);

	//Botón de controles
	posButton = posButton + Vector2D(0, app_->getWindowHeight() / 4 - sizeButton.getY() / 2);
	createButton(app_->getTextureManager()->getTexture(Resources::Controls), posButton, sizeButton, showControls, app_);

	//Botón de menú principal
	posButton = posButton + Vector2D(0, app_->getWindowHeight() / 4 - sizeButton.getY() / 2);
	createButton(app_->getTextureManager()->getTexture(Resources::Controls), posButton, sizeButton, goMainMenuState, app_);
	
	//Botón de mute
}