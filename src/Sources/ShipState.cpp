#include "ShipState.h"
#include "GameManager.h"
#include "Player.h"
#include "ShipObject.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "SelectLevelState.h"
#include "SaveLoadState.h"
#include "StashState.h"

#include "Collisions.h" //Provisional


#pragma region CallBacks
//Callback para cambiar de GameState e ir a la isla actual
void ShipState::goIsland(Application* app)
{
	//Viajamos a la isla correspondiente
	GameManager* gm = GameManager::instance();
	Island currIsland = gm->getCurrIsland();
	if (currIsland == Island::Caribbean) app->getGameStateMachine()->changeState(new CaribbeanIslandState(app));
	else if (currIsland == Island::Spooky) app->getGameStateMachine()->changeState(new SpookyIslandState(app));
	else if (currIsland == Island::Volcanic) app->getGameStateMachine()->changeState(new VolcanicIslandState(app));
}
//Callback del alijo para ir al men� de alijo
void ShipState::goStashState(Application* app)
{
	app->getGameStateMachine()->pushState(new StashState(app));
}
//Callback del mapa
void ShipState::goMap(Application* app)
{
	app->getGameStateMachine()->pushState(new SelectLevelState(app));
}
//Callback para ir al menu de guardado
void ShipState::goSaveState(Application* app)
{
	app->getGameStateMachine()->pushState(new SaveLoadState(app, false));
}
#pragma endregion

void ShipState::initState()
{
	//Borramos la lista de objetos del barco del CollisionCtrl
	collisionCtrl_->clearList();

	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::Ship));
	addRenderUpdateLists(background_);

	SDL_Rect destRect; //Rect�ngulo para los objetos

	//Creaci�n del alijo
	destRect.w = W_STASH; destRect.h = H_STASH;
	destRect.x = W_WIN / 2; destRect.y = H_WIN * 2 / 5;
	stash_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::Stash), goStashState);
	addRenderUpdateLists(stash_);

	//Creaci�n de la trampilla
	destRect.w = W_DOOR; destRect.h = H_DOOR;
	destRect.x = (W_WIN / 2) - W_DOOR * 1.5; destRect.y = H_WIN * 2 / 5 + H_WHEEL / 2;
	door_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ShipDoor), goSaveState);
	addRenderUpdateLists(door_);

	//Creaci�n del timon
	destRect.w = W_WHEEL; destRect.h = H_WHEEL;
	destRect.x = (W_WIN / 2) - W_WHEEL / 2; destRect.y = H_WIN / 7;
	wheel_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::Wheel), goMap);
	addRenderUpdateLists(wheel_);
	
	//Creacion de la salida
	destRect.w = W_EXIT; destRect.h = H_EXIT;
	destRect.x = W_WIN - W_EXIT; destRect.y = H_WIN * 2 / 3;
	exit_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ExitShip), goIsland);
	addRenderUpdateLists(exit_);

	collisionCtrl_->addShipObjects(stash_, door_, wheel_, exit_);

	createNPC();	//Método de testeo de los NPCs del barco, faltaría hacer uno definitivo para todos los NPCs desbloqueados

	////Siempre se a�ade el �ltimo para que se renderice por encima de los dem�s objetos
	playerEntry_ = Vector2D((W_WIN - W_PLAYER * 4), ((H_WIN * 3 / 4) - H_PLAYER));
	player_->setPos(playerEntry_);
	player_->setScale(Vector2D(W_PLAYER, H_PLAYER));
	addRenderUpdateLists(player_);
	addRenderUpdateLists(hud_);
	startInstance_ = SDL_GetTicks();
}

void ShipState::update()
{
	PlayState::update();

	if (!songActive && pirateSingers_ <= SDL_GetTicks() - startInstance_) {
		app_->getAudioManager()->playMusic(Resources::ShipSingers, -1);
		songActive = true;
	}
	collisionCtrl_->shipCollisions();
}

void ShipState::createNPC() {
	int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	NPC* skeleton;
	Vector2D pos;
	pos.setVec(Vector2D(wWin / 2, hWin * 3 / 4));
	skeleton = new NPC(app_, app_->getTextureManager()->getTexture(Resources::SkeletonMusician), pos, Vector2D(app_->getWindowWidth() / 11, app_->getWindowHeight() / 6), 5);
	addRenderUpdateLists(skeleton);
}