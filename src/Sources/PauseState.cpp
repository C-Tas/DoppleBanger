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

void PauseState::draw() const
{
	SDL_Rect bgRect;
	bgRect.x = 0; bgRect.y = 0;
	bgRect.w = backgroundW; bgRect.h = backgroundH;
	background_->render(bgRect);

	GameState::draw();
}

void PauseState::changeMute()
{
	if (app_->getMute())  muteButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteOn));
	else muteButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteOff));
}

void PauseState::initState()
{
	background_ = app_->getTextureManager()->getTexture(Resources::Pause);

	//Creación de botones
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	Vector2D sizeButton(winWidth / 6, winHeight/ 10);
	Vector2D posButton(winWidth / 2 - sizeButton.getX() / 2, winHeight / 4 - sizeButton.getY() / 2);

	//Botón de reanudar
	createButton(app_->getTextureManager()->getTexture(Resources::Resume), posButton, sizeButton, resume, app_);

	//Botón de controles
	posButton = posButton + Vector2D(0, winHeight / 4 - sizeButton.getY() / 2);
	createButton(app_->getTextureManager()->getTexture(Resources::Controls), posButton, sizeButton, showControls, app_);

	//Botón de menú principal
	posButton = posButton + Vector2D(0, winHeight / 4 - sizeButton.getY() / 2);
	createButton(app_->getTextureManager()->getTexture(Resources::BackButton), posButton, sizeButton, goMainMenuState, app_);
	
	//Botón de mute
	//Se multiplica por la proporción winWidth/winHeight para hacer un cuadrado
	sizeButton = Vector2D(winWidth / 20, (winHeight / 20) * (winWidth / winHeight));
	posButton = Vector2D(sizeButton.getX() * 1.5, sizeButton.getY() * 1.5);
	
	muteButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::MuteOff), posButton, sizeButton, muteGame);
	addRenderUpdateLists(muteButton);
}