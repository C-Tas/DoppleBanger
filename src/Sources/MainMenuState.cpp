#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"
#include "Texture.h"
#include "SDL_macros.h"
#include "VisualElement.h"
#include "BeerButton.h"

#include "Clon.h"

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

void MainMenuState::createButtons() {
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	//creamos el boton para ir a los controles
	BeerButton* controlButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ControlsButton), 
		{ (winWidth / 2) - button_w * 1.5  , (winHeight / 2) },
		{ button_w  ,button_h }, goControlState);
	addRenderUpdateLists(controlButton);
	//creamos el boton para ir a los creditos
	BeerButton* creditButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::CreditsButton),
		{ (winWidth / 2) + button_w / 2   , (winHeight / 2) },
		{ button_w  ,button_h }, goCreditsState);
	addRenderUpdateLists(creditButton);
	//creamos el boton para jugar cargando el juego del archivo de guardado
	BeerButton* loadButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButton),
		{ (winWidth / 2) - button_w * 1.5 , (winHeight / 2) + button_h * 1.2 },
		{ button_w,button_h }, goLoadState);
	addRenderUpdateLists(loadButton);

	//creamos el boton para jugar sin cargar el juego del archivo de guardado
	BeerButton* playButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::PlayButton),
		{ (winWidth / 2) + button_w / 2, (winHeight / 2) + button_h * 1.2 },
		{ button_w,button_h }, goStoryState);
	addRenderUpdateLists(playButton);

	//Boton para salir del juego
	BeerButton* exitButton = new BeerButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ExitButton),
		{ (winWidth / 2) - button_w / 2, (winHeight / 2) + button_h * 2.4 },
		{ button_w,button_h }, exitGame);
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
	app->getGameStateMachine()->pushState(new SaveLoadState(app, true)); //TRUE => LOAD //FALSE => SAVE
};
void MainMenuState::goStoryState(Application* app) {
	app->getAudioManager()->playChannel(Resources::Shout, 0, 1);
	app->getGameStateMachine()->pushState(new StoryState(app));
};
void MainMenuState::exitGame(Application* app) {
	app->endGame();
}
#pragma endregion