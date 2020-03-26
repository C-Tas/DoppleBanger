#include "ShipState.h"
#include "Player.h"
#include "ShipObject.h"
#include "Trigger.h"
#include "Collisions.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "GameManager.h"

void goIsland(Application* app, int island) {
	if(island == 1) app->getGameStateMachine()->changeState(new CaribbeanIslandState(app));
	else if(island == 2) app->getGameStateMachine()->changeState(new SpookyIslandState(app));
	else if (island == 3) app->getGameStateMachine()->changeState(new VolcanicIslandState(app));
}
void ShipState::initState()
{
	background_ = app_->getTextureManager()->getTexture(Resources::Ship);

	SDL_Rect destRect; //Rect�ngulo para los objetos

	//Creaci�n del alijo
	destRect.w = wStash; destRect.h = hStash;
	destRect.x = app_->getWindowWidth() / 2; destRect.y = app_->getWindowHeight() * 2 / 5;
	stash_ = new ShipObject(app_, destRect, app_->getTextureManager()->getTexture(Resources::Stash),
		Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h));
	addRenderUpdateLists(stash_);

	//Creaci�n de la trampilla
	destRect.w = wDoor; destRect.h = hDoor;
	destRect.x = (app_->getWindowWidth() / 2) - wDoor * 1.5; destRect.y = app_->getWindowHeight() * 2 / 5 + hWheel / 2;
	door_ = new ShipObject(app_, destRect, app_->getTextureManager()->getTexture(Resources::ShipDoor),
		Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h));
	addRenderUpdateLists(door_);

	//Creaci�n del tim�n
	destRect.w = wWheel; destRect.h = hWheel;
	destRect.x = (app_->getWindowWidth() / 2) - wWheel / 2; destRect.y = app_->getWindowHeight() / 7;
	wheel_ = new ShipObject(app_, destRect, app_->getTextureManager()->getTexture(Resources::Timon),
		Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h));
	addRenderUpdateLists(wheel_);
	
	//Creaci�n del trigger para ir a una isla
	destRect.w = wExit; destRect.h = hExit;
	destRect.x = app_->getWindowWidth() - wExit; destRect.y = app_->getWindowHeight() * 2 / 3;
	GameManager::instance()->setIsland(2); //Para probar con distintas islas poner otro n�mero
	exit_ = new Trigger(app_, destRect, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.w),
		goIsland, player_, GameManager::instance()->getCurrIsland());
	addUpdateList(exit_);


	//Siempre se a�ade el �ltimo para que se renderice por encima de los dem�s objetos
	addRenderUpdateLists(player_);
}

void ShipState::update()
{
	PlayState::update();

	//Esta regi�n est� dise�ada para testear y puede ser usada para c�digo definitivo en caso de que sea �til
#pragma region Testeo
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
			stash_->onColliderStash();
		}
	}

	//Trampilla
	if (RectRect(player_->getPos().getX() + wPlayer / 2, player_->getPos().getY() + hPlayer / 2, player_->getScaleX(), player_->getScaleY() / 10,
		door_->getPos().getX() + wDoor / 2, door_->getPos().getY() + hDoor / 2, door_->getScaleX(), door_->getScaleY())) {
		player_->stop();
		if (doorClick) {
			doorClick = false;
			door_->onColliderDoor();
		}
	}

	//Tim�n
	if (RectRect(player_->getPos().getX() + wPlayer / 2, player_->getPos().getY() + hPlayer / 2, player_->getScaleX(), player_->getScaleY() / 10,
		wheel_->getPos().getX() + wWheel/ 2, wheel_->getPos().getY() + hWheel/ 2, wheel_->getScaleX(), wheel_->getScaleY())) {
		player_->stop();
		if (wheelClick) {
			wheelClick = false;
			//Para cambiar de isla
			wheel_->onColliderWheel(GameManager::instance()->getCurrIsland()); //Hay que pasarle el n�mero de islas desbloqueadas
		}
	}

	//Trigger de salida
	if (RectRect(player_->getPos().getX() + wPlayer / 2, player_->getPos().getY() + hPlayer / 2, player_->getScaleX(), player_->getScaleY(),
		exit_->getPos().getX() + wExit / 2, exit_->getPos().getY() + hExit / 2, exit_->getScaleX(), exit_->getScaleY())) {
		exit_->onOverlap();
	}
#pragma endregion
}
