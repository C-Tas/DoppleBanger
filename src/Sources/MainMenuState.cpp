#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "LoadState.h"
#include "SDL_macros.h"
#include "VisualElement.h"
#include "BeerButton.h"
#include <fstream>

using namespace std;

#pragma region Inicializacion
void MainMenuState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);

	//Fondo de la escena
	button_h = app_->getWindowHeight() / 10;
	button_w = app_->getWindowWidth() / 6;
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
	//Cargamos música de fondo
	app_->getAudioManager()->playChannel(Resources::AudioId::MainTheme, -1, Resources::MainMusicChannel);

	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	//creamos el boton para jugar sin cargar el juego del archivo de guardado
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::PlayButton),
		{ (winWidth / 2) - button_w * 1.5  , (winHeight / 2) },
		{ button_w,button_h }, goStoryState, this);
	//creamos el boton para jugar cargando el juego del archivo de guardado
	Button* loadButton = nullptr;
	if (!isExistingDataGame()) {
		createButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButtonNull),
			{ (winWidth / 2) + button_w / 2, (winHeight / 2) },
			{ button_w,button_h }, nullptr);
	}
	else {
		createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButton),
			{ (winWidth / 2) + button_w / 2, (winHeight / 2) },
			{ button_w,button_h }, goLoadState, this);
	}
	//creamos el boton para ir a los controles
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ControlsButton),
		{ double(app_->getWindowWidth() / 2) - button_w * 1.5, double(app_->getWindowHeight() / 2) + button_h * 1.2 },
		{ button_w  ,button_h }, goControlState, this);
	//creamos el boton para ir a los creditos
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::CreditsButton),
		{ (winWidth / 2) + button_w / 2, double(app_->getWindowHeight() / 2) + button_h * 1.2 },
		{ button_w  ,button_h }, goCreditsState, this);
	//Boton para salir del juego
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ExitButton),
		{ (winWidth / 2) - button_w / 2, (winHeight / 2) + button_h * 2.4 },
		{ button_w,button_h }, exitGame, this);
}
#pragma endregion
#pragma region Cambios de estados
void MainMenuState::goControlState(Application* app) {
	app->getGameStateMachine()->pushState(new ControlsState(app));
};
void MainMenuState::goCreditsState(Application* app) {
	app->getGameStateMachine()->pushState(new CreditsState(app));
};
void MainMenuState::goLoadState(Application* app) {
	app->getGameStateMachine()->pushState(new LoadState(app));
};
void MainMenuState::goStoryState(Application* app) {
	app->resetMusicChannels();
	app->getAudioManager()->playChannel(Resources::Storyboard, -1, Resources::MainMusicChannel);
	app->getGameStateMachine()->pushState(new StoryState(app));
};

void MainMenuState::exitGame(Application* app) {
	app->endGame();
}
#pragma endregion