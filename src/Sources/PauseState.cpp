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
	app->getAudioManager()->resumeChannel(Resources::MainMusicChannel);
	app->getAudioManager()->playChannel(Resources::WavesSound, -1, Resources::AuxMusicChannel1);
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
/// Silencia/Habilita musica y efectos de sonido
///</summary>
void PauseState::muteMusic(Application* app) {
	app->getAudioManager()->setMuteMusic();			//Cambia el booleano que controla el mute
	app->getAudioManager()->setAllMusicVolumen();	//Cambia el volumen en funcion del mute
	static_cast<PauseState*>(app->getGameStateMachine()->getState())->changeMuteMusic(); //Cambia la textura del bot�n mute del PauseState
}

void PauseState::muteSounds(Application* app) {
	app->getAudioManager()->setMuteSounds();		//Cambia el booleano que controla el mute
	app->getAudioManager()->setAllSoundVolumen();	//Cambia el volumen en funcion del mute
	static_cast<PauseState*>(app->getGameStateMachine()->getState())->changeMuteSound(); //Cambia la textura del bot�n mute del PauseState
}
#pragma endregion

PauseState::PauseState(Application* app) : GameState(app) {
	initState();
}

void PauseState::changeMuteMusic()
{
	if (app_->getAudioManager()->getMuteMusic())  muteMusicButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteMusicOn));
	else muteMusicButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteMusicOff));
}

void PauseState::changeMuteSound()
{
	if (app_->getAudioManager()->getMuteSounds())  muteSoundButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteSoundOn));
	else muteSoundButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteSoundOff));
}

void PauseState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);

	app_->resetSoundsChannels();
	app_->getAudioManager()->pauseChannel(Resources::MainMusicChannel);
	app_->getAudioManager()->playChannel(Resources::MainTheme, -1, Resources::AuxMusicChannel1);

	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::PauseBackground));
	addRenderUpdateLists(background_);

	//Creaci�n de botones
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	Vector2D sizeButton(winWidth * 5 / 11, winHeight / 5);
	Vector2D posButton(winWidth / 9 , winHeight / 4 - sizeButton.getY() / 2);

	SDL_Rect textButon = { (int)round(posButton.getX()),(int)round(posButton.getY()), (int)round(sizeButton.getX()),(int)round(sizeButton.getY()) };

	//Bot�n de reanudar
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::ResumeButton), posButton, sizeButton, resume, this);

	//Bot�n de controles
	posButton = posButton + Vector2D(0, winHeight / 4);
	textButon.y = (int)round(posButton.getY());
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::ControlsButton), posButton, sizeButton, showControls, this);

	//Bot�n de men� principal
	posButton = posButton + Vector2D(0, winHeight / 4 );
	textButon.y =(int)round(posButton.getY());
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::GoMainMenuButton), posButton, sizeButton, goMainMenuState, this);
	
	//Botones de mute
	//Se multiplica por la proporci�n winWidth/winHeight para hacer un cuadrado
	//No se crea con el metodo createButton porque se necesita un puntero a él directo
	//para cambiar la textura al hacer el mute
	sizeButton = Vector2D(winWidth / 20, (winHeight / 20) * (winWidth / winHeight));
	posButton = Vector2D(winWidth - (sizeButton.getX() * 1.5), sizeButton.getY() / 2);
	
	if (!app_->getAudioManager()->getMuteSounds()) muteSoundButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::MuteSoundOff), posButton, sizeButton, muteSounds);
	else muteSoundButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::MuteSoundOn), posButton, sizeButton, muteSounds);
	addRenderUpdateLists(muteSoundButton);

	posButton = Vector2D(winWidth - (sizeButton.getX() * 3), sizeButton.getY() / 2);

	if (!app_->getAudioManager()->getMuteMusic()) muteMusicButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::MuteMusicOff), posButton, sizeButton, muteMusic);
	else muteMusicButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::MuteMusicOn), posButton, sizeButton, muteMusic);
	addRenderUpdateLists(muteMusicButton);
}