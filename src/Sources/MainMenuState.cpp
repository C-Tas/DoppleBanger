#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"
#include "Button.h"
#include "Texture.h"
#include "SDL_macros.h"
#include "VisualElement.h"

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
	//creamos el boton para ir a los controles
	Button* controlButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ControlsButton),
		{ double(app_->getWindowWidth() / 2) - button_w * 1.5  ,(double)(app_->getWindowHeight() / 2) },
		{ button_w  ,button_h }, goControlState);
	gameObjects_.push_back(controlButton);
	objectsToRender_.push_back(controlButton);
	//creamos el boton para ir a los creditos
	Button* creditButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::CreditsButton),
		{ double(app_->getWindowWidth() / 2) + button_w / 2   , (double)(app_->getWindowHeight() / 2) },
		{ button_w  ,button_h }, goCreditsState);
	gameObjects_.push_back(creditButton);
	objectsToRender_.push_back(creditButton);
	//creamos el boton para jugar cargando el juego del archivo de guardado
	Button* loadButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::LoadButton),
		{ double(app_->getWindowWidth() / 2) - button_w * 1.5 ,double(app_->getWindowHeight() / 2) + button_h * 1.2 },
		{ button_w,button_h }, goLoadState);
	gameObjects_.push_back(loadButton);
	objectsToRender_.push_back(loadButton);
	//creamos el boton para jugar sin cargar el juego del archivo de guardado
	Button* playButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::PlayButton),
		{ double(app_->getWindowWidth() / 2) + button_w / 2,double(app_->getWindowHeight() / 2) + button_h * 1.2 },
		{ button_w,button_h }, goStoryState);
	gameObjects_.push_back(playButton);
	objectsToRender_.push_back(playButton);

	//Boton para salir del juego
	Button* exitButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ExitButton),
		{ double(app_->getWindowWidth() / 2) - button_w / 2,double(app_->getWindowHeight() / 2) + button_h * 2.4 },
		{ button_w,button_h }, exitGame);
	gameObjects_.push_back(exitButton);
	objectsToRender_.push_back(exitButton);

#ifdef _DEBUG
	cout << "creados los botones correctamente"<<endl;
#endif
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
	app->getGameManager()->setCompleteMission(missions::gallegaEnProblemas, false);
	app->getGameManager()->setStartedMission(missions::gallegaEnProblemas, false);
	app->getGameStateMachine()->pushState(new StoryState(app));
};
void MainMenuState::exitGame(Application* app) {
	app->endGame();
}
#pragma endregion