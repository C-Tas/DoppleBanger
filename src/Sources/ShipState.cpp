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
	GameManager* gm = GameManager::instance();
	if (gm->getCurrIsland() == Island::Caribbean) app->getGameStateMachine()->changeState(new CaribbeanIslandState(app));
	else if (gm->getCurrIsland() == Island::Spooky) app->getGameStateMachine()->changeState(new SpookyIslandState(app));
	else if (gm->getCurrIsland() == Island::Volcanic) app->getGameStateMachine()->changeState(new VolcanicIslandState(app));
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
	collisionCtrl_ = CollisionCtrl::instance();
	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::Ship));
	addRenderUpdateLists(background_);

	SDL_Rect destRect; //Rect�ngulo para los objetos

	//Creaci�n del alijo
	destRect.w = W_STASH; destRect.h = H_STASH;
	destRect.x = app_->getWindowWidth() / 2; destRect.y = app_->getWindowHeight() * 2 / 5;
	stash_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h), 
		app_->getTextureManager()->getTexture(Resources::Stash), goStashState);
	addRenderUpdateLists(stash_);

	//Creaci�n de la trampilla
	destRect.w = W_DOOR; destRect.h = H_DOOR;
	destRect.x = (app_->getWindowWidth() / 2) - W_DOOR * 1.5; destRect.y = app_->getWindowHeight() * 2 / 5 + H_WHEEL / 2;
	door_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ShipDoor), goSaveState);
	addRenderUpdateLists(door_);

	//Creaci�n del tim�n
	destRect.w = W_WHEEL; destRect.h = H_WHEEL;
	destRect.x = (app_->getWindowWidth() / 2) - W_WHEEL / 2; destRect.y = app_->getWindowHeight() / 7;
	wheel_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::Wheel), goMap);
	addRenderUpdateLists(wheel_);
	
	//Creaci�n de la salida
	destRect.w = W_EXIT; destRect.h = H_EXIT;
	destRect.x = app_->getWindowWidth() - W_EXIT; destRect.y = app_->getWindowHeight() * 2 / 3;
	exit_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ExitShip), goIsland);
	addRenderUpdateLists(exit_);

	////Siempre se a�ade el �ltimo para que se renderice por encima de los dem�s objetos
	playerEntry_ = Vector2D((app_->getWindowWidth() - W_PLAYER * 2), ((app_->getWindowHeight() * 3 / 4) - H_PLAYER));
	player_ = new Player(app_, playerEntry_, Vector2D(W_PLAYER, H_PLAYER));
	addRenderUpdateLists(player_);

	startInstance_ = SDL_GetTicks();
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
	if (!songActive && pirateSingers_ <= SDL_GetTicks() - startInstance_) {
		app_->getAudioManager()->playMusic(Resources::ShipSingers, -1);
		songActive = true;

	}

	//Colisiones con los objetos del barco
	//Alijo
	if (RectRect(player_->getPos().getX() + W_PLAYER / 2, player_->getPos().getY() + H_PLAYER / 2, player_->getScaleX(), player_->getScaleY() / 10,
		stash_->getPos().getX() + W_STASH / 2, stash_->getPos().getY() + H_STASH / 2, stash_->getScaleX(), stash_->getScaleY())) {
		player_->stop();
		if (stashClick) {
			stashClick = false;
			stash_->onCollider();
		}
	}

	//Trampilla
	if (RectRect(player_->getPos().getX() + W_PLAYER / 2, player_->getPos().getY() + H_PLAYER / 2, player_->getScaleX(), player_->getScaleY() / 10,
		door_->getPos().getX() + W_DOOR / 2, door_->getPos().getY() + H_DOOR / 2, door_->getScaleX(), door_->getScaleY())) {
		player_->stop();
		if (doorClick) {
			doorClick = false;
			door_->onCollider();
		}
	}

	//Tim�n
	if (RectRect(player_->getPos().getX() + W_PLAYER / 2, player_->getPos().getY() + H_PLAYER / 2, player_->getScaleX(), player_->getScaleY() / 10,
		wheel_->getPos().getX() + W_WHEEL / 2, wheel_->getPos().getY() + H_WHEEL / 2, wheel_->getScaleX(), wheel_->getScaleY())) {
		player_->stop();
		if (wheelClick) {
			wheelClick = false;
			//Para cambiar de isla
			wheel_->onCollider();
		}
	}

	//Trigger de salida
	if (RectRect(player_->getPos().getX() + W_PLAYER / 2, player_->getPos().getY() + H_PLAYER / 2, player_->getScaleX(), player_->getScaleY(),
		exit_->getPos().getX() + W_EXIT / 2, exit_->getPos().getY() + H_EXIT / 2, exit_->getScaleX(), exit_->getScaleY())) {
		if (exitClick) {
			exitClick = false;
			exit_->onCollider();
		}
	}
#pragma endregion
}
