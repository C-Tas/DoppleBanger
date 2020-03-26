#include "PlayState.h"
#include "PauseState.h"
#include "SaveLoadState.h"
#include "InventoryState.h"
#include "SelectLevelState.h"
#include "StashState.h"
#include "Player.h"

PlayState::PlayState(Application* app) : GameState(app)
{
	//Si no hay player significa que se viene desde el menú, así que se crea. Si no, pues solo se le setea la posición
	SDL_Rect destRect;
	destRect.w = wPlayer; destRect.h = hPlayer;
	destRect.x = app_->getWindowWidth() - wPlayer * 2;
	destRect.y = (app_->getWindowHeight() * 3 / 4) - hPlayer; 

	player_ = new Player(app_, app_->getTextureManager()->getTexture(Resources::PirateFront), Vector2D(destRect.x, destRect.y),
		Vector2D(destRect.w, destRect.h), destRect);
}

#pragma region ChangeState
void PlayState::goToPauseState(Application* app) {
	app->getStateMachine()->pushState(new PauseState(app));
}

void PlayState::goToInventoryState(Application* app) {
	app->getStateMachine()->pushState( new InventoryState(app));

}
void PlayState::draw() const
{
	SDL_Rect destRect;
	destRect.x = 0; destRect.y = 0;
	destRect.w = app_->getWindowWidth();
	destRect.h = app_->getWindowHeight();

	background_->render(destRect);

	GameState::draw();
}
#pragma endregion

//Esta podria ser una clase padre de 4 clases que sean Ship, Island0, Island1 e Island2 de tal forma que al cambiar en SelectLevelState
// al hacer el pop de ese estado no de problemas de ejecucion al tener que cambiar la isla o hacer metodos a los que llamar