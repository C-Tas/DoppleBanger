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

	//Cargamos música de fondo
	app_->getAudioManager()->playMusic(Resources::MainTheme, -1);

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
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	//creamos el boton para ir a los controles
	BeerButton* controlButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ControlsButton), 
		{ (winWidth / 2) - button_w * 1.5  , (winHeight / 2) },
		{ button_w  ,button_h }, goControlState);
	controlButton->setCurrentState(this);
	addRenderUpdateLists(controlButton);
	//creamos el boton para ir a los creditos
	BeerButton* creditButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::CreditsButton),
		{ (winWidth / 2) + button_w / 2   , (winHeight / 2) },
		{ button_w  ,button_h }, goCreditsState);
	creditButton->setCurrentState(this);
	addRenderUpdateLists(creditButton);
	//creamos el boton para jugar cargando el juego del archivo de guardado
	Button* loadButton = nullptr;
	if (!isExistingDataGame()) {
		loadButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButtonNull),
			{ double(app_->getWindowWidth() / 2) - button_w * 1.5 ,double(app_->getWindowHeight() / 2) + button_h * 1.2 },
			{ button_w,button_h }, nullptr);	
	}
	else {
		loadButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButton),
			{ double(app_->getWindowWidth() / 2) - button_w * 1.5 ,double(app_->getWindowHeight() / 2) + button_h * 1.2 },
			{ button_w,button_h }, goLoadState);
	}
	loadButton->setCurrentState(this);
	addRenderUpdateLists(loadButton);

	//creamos el boton para jugar sin cargar el juego del archivo de guardado
	BeerButton* playButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::PlayButton),
		{ (winWidth / 2) + button_w / 2, (winHeight / 2) + button_h * 1.2 },
		{ button_w,button_h }, goStoryState);
	playButton->setCurrentState(this);
	addRenderUpdateLists(playButton);

	//Boton para salir del juego
	BeerButton* exitButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ExitButton),
		{ (winWidth / 2) - button_w / 2, (winHeight / 2) + button_h * 2.4 },
		{ button_w,button_h }, exitGame);
	exitButton->setCurrentState(this);
	addRenderUpdateLists(exitButton);
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
	app->getAudioManager()->playChannel(Resources::Shout, 0, 1);
	app->getGameManager()->setCompleteMission(missions::gallegaEnProblemas, false);
	app->getGameManager()->setStartedMission(missions::gallegaEnProblemas, false);
	app->getGameStateMachine()->pushState(new StoryState(app));
};
void MainMenuState::exitGame(Application* app) {
	app->endGame();
}
#pragma endregion