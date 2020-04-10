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
void goIsland(Application* app) {
	GameManager* gm = GameManager::instance();
	if(gm->getCurrIsland() == Island::Caribbean) app->getGameStateMachine()->changeState(new CaribbeanIslandState(app));
	else if(gm->getCurrIsland() == Island::Spooky) app->getGameStateMachine()->changeState(new SpookyIslandState(app));
	else if (gm->getCurrIsland() == Island::Volcanic) app->getGameStateMachine()->changeState(new VolcanicIslandState(app));
}
//Callback del alijo para ir al men� de alijo
void goStashState(Application* app) {
	app->getGameStateMachine()->pushState(new StashState(app));
}
//Callback del mapa
void goMap(Application* app) {
	GameManager* gm = GameManager::instance();
	app->getGameStateMachine()->pushState(new SelectLevelState(app));
}
//Callback para ir al men� de guardado
void goSaveState(Application* app) {
	app->getGameStateMachine()->pushState(new SaveLoadState(app, false));
}
#pragma endregion

void ShipState::initState()
{
	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::Ship));
	addRenderUpdateLists(background_);

	SDL_Rect destRect; //Rect�ngulo para los objetos

	//Creaci�n del alijo
	destRect.w = wStash; destRect.h = hStash;
	destRect.x = app_->getWindowWidth() / 2; destRect.y = app_->getWindowHeight() * 2 / 5;
	stash_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h), 
		app_->getTextureManager()->getTexture(Resources::Stash), goStashState);
	addRenderUpdateLists(stash_);

	//Creaci�n de la trampilla
	destRect.w = wDoor; destRect.h = hDoor;
	destRect.x = (app_->getWindowWidth() / 2) - wDoor * 1.5; destRect.y = app_->getWindowHeight() * 2 / 5 + hWheel / 2;
	door_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ShipDoor), goSaveState);
	addRenderUpdateLists(door_);

	//Creaci�n del tim�n
	destRect.w = wWheel; destRect.h = hWheel;
	destRect.x = (app_->getWindowWidth() / 2) - wWheel / 2; destRect.y = app_->getWindowHeight() / 7;
	wheel_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::Wheel), goMap);
	addRenderUpdateLists(wheel_);
	
	//Creaci�n de la salida
	destRect.w = wExit; destRect.h = hExit;
	destRect.x = app_->getWindowWidth() - wExit; destRect.y = app_->getWindowHeight() * 2 / 3;
	exit_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ExitShip), goIsland);
	addRenderUpdateLists(exit_);


	playerEntry_ = Vector2D((app_->getWindowWidth() - wPlayer * 2), ((app_->getWindowHeight() * 3 / 4) - hPlayer));
	player_->setPos(playerEntry_);
	player_->setScale(Vector2D(wPlayer, hPlayer));

	addRenderUpdateLists(player_);
	addRenderUpdateLists(hud_);
}


void ShipState::update()
{
	PlayState::update();

#pragma region ColisionesProvisional
	HandleEvents* input = HandleEvents::instance();

	Vector2D aux = input->getMousePos(); //Guardas la posicion del raton

	//Comprueba si se ha hecho click en los objetos para habilitar su evento de colisi�n
	if (input->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		mouse = { (int)aux.getX(), (int)aux.getY() };
		if (SDL_PointInRect(&mouse, &stash_->getDestiny())) {
			stashClick = true;
		}
		else if (SDL_PointInRect(&mouse, &door_->getDestiny())) {
			doorClick = true;
		}
		else if (SDL_PointInRect(&mouse, &wheel_->getDestiny())) {
			wheelClick = true;
		}
		else if (SDL_PointInRect(&mouse, &exit_->getDestiny())) {
			exitClick = true;
		}
		else {
			stashClick = false;
			doorClick = false;
			wheelClick = false;
		}
	}

	//Colisiones con los objetos del barco
	//Alijo
	if (RectRect(player_->getPos().getX() + wPlayer / 2, player_->getPos().getY() + hPlayer / 2, player_->getScaleX(), player_->getScaleY() / 10,
		stash_->getPos().getX() + wStash / 2, stash_->getPos().getY() + hStash / 2, stash_->getScaleX(), stash_->getScaleY())) {
		player_->stop();
		if (stashClick) {
			stashClick = false;
			stash_->onCollider();
		}
	}

	//Trampilla
	if (RectRect(player_->getPos().getX() + wPlayer / 2, player_->getPos().getY() + hPlayer / 2, player_->getScaleX(), player_->getScaleY() / 10,
		door_->getPos().getX() + wDoor / 2, door_->getPos().getY() + hDoor / 2, door_->getScaleX(), door_->getScaleY())) {
		player_->stop();
		if (doorClick) {
			doorClick = false;
			door_->onCollider();
		}
	}

	//Tim�n
	if (RectRect(player_->getPos().getX() + wPlayer / 2, player_->getPos().getY() + hPlayer / 2, player_->getScaleX(), player_->getScaleY() / 10,
		wheel_->getPos().getX() + wWheel / 2, wheel_->getPos().getY() + hWheel / 2, wheel_->getScaleX(), wheel_->getScaleY())) {
		player_->stop();
		if (wheelClick) {
			wheelClick = false;
			//Para cambiar de isla
			wheel_->onCollider();
		}
	}

	//Trigger de salida
	if (RectRect(player_->getPos().getX() + wPlayer / 2, player_->getPos().getY() + hPlayer / 2, player_->getScaleX(), player_->getScaleY(),
		exit_->getPos().getX() + wExit / 2, exit_->getPos().getY() + hExit / 2, exit_->getScaleX(), exit_->getScaleY())) {
		if (exitClick) {
			exitClick = false;
			exit_->onCollider();
		}
	}
#pragma endregion
}
