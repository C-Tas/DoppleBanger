#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"

void MainMenuState::initMenuState()
{
	eventHandler_ = HandleEvents::instance();
	//meter botones etc..

	//Comprobación del generador aleatorio de equipamiento
	/*for (int i = 0; i < 5; i++)
	{
		Equipment* equip = app_->genEquip();
		equip->writeStats();
		cout << "\n";
	}*/

	Texture* playerTexture = new Texture(app_->getRenderer(), "../Sources/assets/timon.png");
	SDL_Rect playerCollision; playerCollision.x = 0; playerCollision.y = 0; playerCollision.w = 0; playerCollision.h = 0;
	player_ = new Player(app_, playerTexture, Vector2D(50, 50), Vector2D(50, 50), playerCollision);
	addUpdateList(player_);
	addRenderList(player_);
}

void MainMenuState::goControlState() {
	app_->getStateMachine()->pushState( new ControlsState(app_));
};
void MainMenuState::goCreditsState() {
	app_->getStateMachine()->pushState( new CreditsState(app_));
};
void MainMenuState::goLoadState() {
	app_->getStateMachine()->pushState(new SaveLoadState(app_, true)); //TRUE => LOAD //FALSE => SAVE
};
void MainMenuState::goStoryState() {
	app_->getStateMachine()->pushState( new StoryState(app_));
};