#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"
#include "Button.h"
#include "Texture.h"
#include "SDL_macros.h"

using namespace std;

#pragma region Inicializacion
void MainMenuState::initMenuState()
{
#ifdef _DEBUG
	cout << "\n" << "---------------" << "\n";
	//Comprobaci�n del generador aleatorio de equipamiento
	//El primer valor es el tipo de equipamiento, y se puede ver en el struct equipType en Equipment.h
	for (int i = 0; i < 5; i++)
	{
		Equipment* equip = app_->genEquip();
		player_->equip(equip);
	}
#endif // _DEBUG

	//Fondo de la escena
	button_h = app_->getWindowHeight() / 10;
	button_w = app_->getWindowWidth() / 6;
	bg_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::MenuFondo));
	objectsToRender_.push_back(bg_);
	gameObjects_.push_back(bg_);

	//Cargamos música de fondo
	app_->getAudioManager()->playMusic(Resources::MainTheme, -1);
	app_->getAudioManager()->setMusicVolume(5);

	//Cargamos un objeto con el fondo(tipo Draw)
	createButtons();

}

void MainMenuState::createButtons() {
	//creamos el boton para ir a los controles
	Button* controlButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BotonMenu),
		{ double(app_->getWindowWidth() / 2) - button_w * 1.5  ,(double)(app_->getWindowHeight() / 2) },
		{ button_w  ,button_h }, goControlState);
	gameObjects_.push_back(controlButton);
	objectsToRender_.push_back(controlButton);
	Draw* controlText = new Draw(app_, app_->getTextureManager()->getTexture(Resources::ControlsText), controlButton->getDestiny());
	objectsToRender_.push_back(controlText);
	gameObjects_.push_back(controlText);
	//creamos el boton para ir a los creditos
	Button* creditButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BotonMenu),
		{ double(app_->getWindowWidth() / 2) + button_w / 2   , (double)(app_->getWindowHeight() / 2) },
		{ button_w  ,button_h }, goCreditsState);
	gameObjects_.push_back(creditButton);
	objectsToRender_.push_back(creditButton);
	Draw* creditText = new Draw(app_, app_->getTextureManager()->getTexture(Resources::CreditsText), creditButton->getDestiny());
	objectsToRender_.push_back(creditText);
	gameObjects_.push_back(creditText);
	//creamos el boton para jugar cargando el juego del archivo de guardado
	Button* loadButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BotonMenu),
		{ double(app_->getWindowWidth() / 2) - button_w * 1.5 ,double(app_->getWindowHeight() / 2) + button_h * 1.2 },
		{ button_w,button_h }, goLoadState);
	gameObjects_.push_back(loadButton);
	objectsToRender_.push_back(loadButton);
	Draw* loadText = new Draw(app_, app_->getTextureManager()->getTexture(Resources::LoadText), loadButton->getDestiny());
	objectsToRender_.push_back(loadText);
	gameObjects_.push_back(loadText);
	//creamos el boton para jugar sin cargar el juego del archivo de guardado
	Button* playButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BotonMenu),
		{ double(app_->getWindowWidth() / 2) + button_w / 2,double(app_->getWindowHeight() / 2) + button_h * 1.2 },
		{ button_w,button_h }, goStoryState);
	gameObjects_.push_back(playButton);
	objectsToRender_.push_back(playButton);
	Draw* playText = new Draw(app_, app_->getTextureManager()->getTexture(Resources::PlayText), playButton->getDestiny());
	objectsToRender_.push_back(playText);
	gameObjects_.push_back(playText);

	//Boton para salir del juego
	Button* exitButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BotonMenu),
		{ double(app_->getWindowWidth() / 2) - button_w / 2,double(app_->getWindowHeight() / 2) + button_h * 2.4 },
		{ button_w,button_h }, exitGame);
	gameObjects_.push_back(exitButton);
	objectsToRender_.push_back(exitButton);
	Draw* exitText = new Draw(app_, app_->getTextureManager()->getTexture(Resources::ExitText), exitButton->getDestiny());
	objectsToRender_.push_back(exitText);
	gameObjects_.push_back(exitText);


#ifdef _DEBUG
	cout << "creados los botones correctamente"<<endl;
#endif
}
#pragma endregion
#pragma region Cambios de estados
void MainMenuState::goControlState(Application* app) {
	app->getStateMachine()->pushState(new ControlsState(app));
};
void MainMenuState::goCreditsState(Application* app) {
	app->getStateMachine()->pushState(new CreditsState(app));
};
void MainMenuState::goLoadState(Application* app) {
	app->getStateMachine()->pushState(new SaveLoadState(app, true)); //TRUE => LOAD //FALSE => SAVE
};
void MainMenuState::goStoryState(Application* app) {
	app->getStateMachine()->pushState(new StoryState(app));
};
void MainMenuState::exitGame(Application* app) {
	app->endGame();
}
#pragma endregion