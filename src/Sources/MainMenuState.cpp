#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "LoadState.h"
#include "SDL_macros.h"
#include "VisualElement.h"
#include "BeerButton.h"
#include <fstream>
#include "Tracker.h"
#include "Login.h"

using namespace std;

#pragma region Callbacks
void MainMenuState::goControlState(Application* app) {
	app->getGameStateMachine()->pushState(new ControlsState(app));
};
void MainMenuState::goCreditsState(Application* app) {
	app->getGameStateMachine()->pushState(new CreditsState(app));
};
void MainMenuState::goLoadState(Application* app) {
	app->getGameStateMachine()->pushState(new LoadState(app));

	// USABILIDAD
	int timest = std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::system_clock::now().time_since_epoch()).count();
	Login* login = (Login*)(Tracker::CreateNewEvent(timest, "a", "a", (int)EventInfo::EventType::Login));
	Tracker::TrackEvent(login);
};
void MainMenuState::goStoryState(Application* app) {
	app->resetMusicChannels();
	app->getAudioManager()->playChannel(Resources::Storyboard, -1, Resources::MainMusicChannel);
	app->getGameStateMachine()->pushState(new StoryState(app));

	// USABILIDAD
	//Login* login = (Login*)(Tracker::CreateNewEvent(0, "a", "a", (int)EventInfo::EventType::Login));
	//Tracker::TrackEvent(login);
};

void MainMenuState::exitGame(Application* app) {
	app->endGame();
}

///<summary>
/// Silencia/Habilita musica y efectos de sonido
///</summary>
void MainMenuState::muteMusic(Application* app) {
	app->getAudioManager()->setMuteMusic();			//Cambia el booleano que controla el mute
	app->getAudioManager()->setAllMusicVolumen();	//Cambia el volumen en funcion del mute
	static_cast<MainMenuState*>(app->getGameStateMachine()->getState())->changeMuteMusic(); //Cambia la textura del boton mute del PauseState
}

void MainMenuState::muteSounds(Application* app) {
	app->getAudioManager()->setMuteSounds();		//Cambia el booleano que controla el mute
	app->getAudioManager()->setAllSoundVolumen();	//Cambia el volumen en funcion del mute
	static_cast<MainMenuState*>(app->getGameStateMachine()->getState())->changeMuteSound(); //Cambia la textura del boton mute del PauseState
}
#pragma endregion

void MainMenuState::changeMuteMusic()
{
	if (app_->getAudioManager()->getMuteMusic())  muteMusicButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteMusicOn));
	else muteMusicButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteMusicOff));
}

void MainMenuState::changeMuteSound()
{
	if (app_->getAudioManager()->getMuteSounds())  muteSoundButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteSoundOn));
	else muteSoundButton->setTexture(app_->getTextureManager()->getTexture(Resources::MuteSoundOff));
}

#pragma region Inicializacion
void MainMenuState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);

	//Fondo de la escena
	bg_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::MenuBackground));
	addRenderUpdateLists(bg_);

	//Cargamos un objeto con el fondo(tipo Draw)
	createButtons();
}
bool MainMenuState::isExistingDataGame()
{
	ifstream slot1("../Sources/save_data/save1.json");
	ifstream slot2("../Sources/save_data/save2.json");
	ifstream slot3("../Sources/save_data/save3.json");
	if (slot1.fail() && slot2.fail() && slot3.fail()) {
		slot1.close();
		slot2.close();
		slot3.close();
		return false;
	}
	slot1.close();
	slot2.close();
	slot3.close();
	return true;
}

void MainMenuState::createButtons() {
	//Cargamos m�sica de fondo
	app_->getAudioManager()->playChannel(Resources::AudioId::MainTheme, -1, Resources::MainMusicChannel);

	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	button_w = winWidth / 6;
	button_h =winHeight / 10;
	Vector2D sizeButton = Vector2D(button_w, button_h);
	Vector2D posButton = Vector2D((winWidth / 2) - button_w * 1.5, (winHeight / 2));
	//creamos el boton para jugar sin cargar el juego del archivo de guardado
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::PlayButton), posButton, sizeButton, goStoryState, this);

	//creamos el boton para jugar cargando el juego del archivo de guardado
	posButton = Vector2D((winWidth / 2) + button_w / 2, (winHeight / 2));
	Button* loadButton = nullptr;
	if (!isExistingDataGame()) {
		createButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButtonNull), posButton, sizeButton, nullptr);
	}
	else {
		createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButton), posButton, sizeButton, goLoadState, this);
	}

	//creamos el boton para ir a los controles
	posButton = Vector2D((winWidth / 2) - button_w * 1.5, (winHeight / 2) + button_h * 1.2);
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ControlsButton), posButton, sizeButton, goControlState, this);
	//creamos el boton para ir a los creditos
	posButton = Vector2D((winWidth / 2) + button_w / 2, (winHeight / 2) + button_h * 1.2);
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::CreditsButton), posButton, sizeButton, goCreditsState, this);
	//Boton para salir del juego
	posButton = Vector2D((winWidth / 2) - button_w / 2, (winHeight / 2) + button_h * 2.4);
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ExitButton), posButton, sizeButton, exitGame, this);

	//Botones de mute
	//Se multiplica por la proporcion winWidth/winHeight para hacer un cuadrado
	//No se crea con el metodo createButton porque se necesita un puntero a �l directo
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
#pragma endregion