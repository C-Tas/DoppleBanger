#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"
#include "Button.h"
#include "Texture.h"

using namespace std;

#pragma region Inicializacion
void MainMenuState::initMenuState()
{
	//meter botones etc..
	SDL_Rect playerCollision; playerCollision.x = 0; playerCollision.y = 0; playerCollision.w = 0; playerCollision.h = 0;
	player_ = new Player(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(50, 50), Vector2D(100, 100), playerCollision);

	addUpdateList(player_);
	addRenderList(player_);

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

	//Cargamos un objeto con el fondo(tipo Draw)
	createButtons();
}

void MainMenuState::createButtons() {
	//creamos el boton para ir a los controles
	Button* b = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 50,50 }, { 50,50 }, goControlState);
	gameObjects_.push_back(b);
	objectsToRender_.push_back(b);
	//creamos el boton para ir a los creditos
	Button* b1 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 150,50 }, { 50,50 }, goCreditsState);
	gameObjects_.push_back(b1);
	objectsToRender_.push_back(b1);
	//creamos el boton para jugar cargando el juego del archivo de guardado
	Button* b2 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 50,150 }, { 50,50 }, goLoadState);
	gameObjects_.push_back(b2);
	objectsToRender_.push_back(b2);
	//creamos el boton para jugar sin cargar el juego del archivo de guardado
	Button* b3 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 150,150 }, { 50,50 }, goStoryState);
	gameObjects_.push_back(b3);
	objectsToRender_.push_back(b3);
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
#pragma endregion