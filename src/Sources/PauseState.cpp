#include "PauseState.h"
#include "ControlsState.h"
#include "GameManager.h"
#include "VisualElement.h"
#include "BeerButton.h"

#pragma region CallBacks
///<summary>Reanuda la partida actual</summary>
void PauseState::resume(Application* app)
{
	SDL_ShowCursor(SDL_DISABLE);
	app->getAudioManager()->playMusic(Resources::Waves, -1);
	app->getGameStateMachine()->popState();
}
///<summary>Muestra los controles</summary>
void PauseState::showControls(Application* app) {
	app->getGameStateMachine()->pushState(new ControlsState(app));
}

///<summary>Vuelve al men� principal sin guardar partida</summary>
void PauseState::goMainMenuState(Application* app) {
	app->getGameStateMachine()->clearAllStateExceptFirst();
}

///<summary>
/// Silencia/Habilita el sonido
/// Nota: Los efectos de sonido viajan a trav�s de diversos canales y no se pueden silenciar. Los canales funcionan
/// de tal manera que al darle playChannel(...) con loop = 0 estos se activan. Por ello, la forma de que los efectos de sonido no suenen
/// es que se controlen en los sitios en los que se efect�an. En caso de que la m�sica vaya a sonar por canales habr� que hacer los respectivos cambios.
///</summary>
void PauseState::muteGame(Application* app) {
	if (app->getMute()) app->getAudioManager()->setMusicVolume(6); //Reanuda la música
	else app->getAudioManager()->setMusicVolume(0); //Pausa la m�sica

	app->setMute(); //Cambia el booleano que controla el mute
	static_cast<PauseState*>(app->getGameStateMachine()->getState())->changeMute(); //Cambia la textura del bot�n mute del PauseState
}
#pragma endregion

PauseState::PauseState(Application* app) : GameState(app) {
	initState();
}

void PauseState::changeMute()
{
	if (app_->getMute())  muteButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteOn));
	else muteButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteOff));
}

void PauseState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);

	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::PauseBackground));
	addRenderUpdateLists(background_);

	//Creaci�n de botones
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	Vector2D sizeButton(winWidth * 5 / 11, winHeight / 5);
	Vector2D posButton(winWidth / 9 , winHeight / 4 - sizeButton.getY() / 2);

	SDL_Rect textButon = { posButton.getX(),posButton.getY(), sizeButton.getX(),sizeButton.getY() };

	//Bot�n de reanudar
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::ResumeButton), posButton, sizeButton, resume, this);

	//Bot�n de controles
	posButton = posButton + Vector2D(0, winHeight / 4);
	textButon.y = posButton.getY();
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::ControlsButton), posButton, sizeButton, showControls, this);

	//Bot�n de men� principal
	posButton = posButton + Vector2D(0, winHeight / 4 );
	textButon.y = posButton.getY();
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::GoMainMenuButton), posButton, sizeButton, goMainMenuState, this);
	
	//Bot�n de mute
	//Se multiplica por la proporci�n winWidth/winHeight para hacer un cuadrado
	//No se crea con el metodo createButton porque se necesita un puntero a él directo
	//para cambiar la textura al hacer el mute
	sizeButton = Vector2D(winWidth / 20, (winHeight / 20) * (winWidth / winHeight));
	posButton = Vector2D(winWidth - (sizeButton.getX() * 1.5), sizeButton.getY() / 2);
	
	if (!app_->getMute()) muteButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::MuteOff), posButton, sizeButton, muteGame);
	else muteButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::MuteOn), posButton, sizeButton, muteGame);
	addRenderUpdateLists(muteButton);
}
