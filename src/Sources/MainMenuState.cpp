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
	//meter botones etc..

	//Comprobaci�n del generador aleatorio de equipamiento
	/*for (int i = 0; i < 5; i++)
	{
		Equipment* equip = app_->genEquip();
		equip->writeStats();
		cout << "\n";
	}*/

	SDL_Rect playerCollision; playerCollision.x = 50; playerCollision.y = 50; playerCollision.w = 100; playerCollision.h = 100;
	player_ = new Player(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), Vector2D(50, 50), Vector2D(100, 100), playerCollision);

	addUpdateList(player_);
	addRenderList(player_);
#ifdef _DEBUG
	cout << "MainMenuState" << endl;
#endif // _DEBUG

	//Cargamos un objeto con el fondo(tipo Draw)
	createButtons();

	SDL_Rect npcCollision; npcCollision.x = 850; npcCollision.y = 50; npcCollision.w = 100; npcCollision.h = 100;
	npc_ = new NPC(app_, npcCollision, app_->getTextureManager()->getTexture(Resources::TextureId::GoControls), Vector2D(850, 50), Vector2D(100, 100));
	addUpdateList(npc_);
	addRenderList(npc_);
}

void MainMenuState::createButtons() {
	//creamos el boton para ir a los controles
	Button* b = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GoControls), { 50,50 }, { 50,50 }, goControlState);
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

void MainMenuState::update() {	//Update temporal
	GameState::update(); //Para el update de os objetos
	if (SDL_HasIntersection(&player_->getCollider(), &npc_->getCollider())) {	//El textBox se genera cuando haya colisión con el npc
		//Genera textBox
		npc_->getTextBox().dialogElderMan(0);	
		
		//El GameState se encarga de llevar que misiones secundarias están desbloqueadas,
		//así como si se viaja a una isla por primera vez.
	}
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