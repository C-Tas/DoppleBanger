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

	createNPCs();	//Método de testeo de los NPCs del barco, faltaría hacer uno definitivo para todos los NPCs desbloqueados

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

void ShipState::createNPCs() {
	//El viejo y el mercader están desde el principio
	NPC* elderman;
	elderman = new NPC(app_, app_->getTextureManager()->getTexture(Resources::SkeletonMusician), Vector2D(W_WIN / 3, (double)H_WIN / 7), Vector2D(W_ELDERMAN, H_ELDERMAN), 0);
	addRenderUpdateLists(elderman);

	NPC* merchant;
	merchant = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Merchant), Vector2D((double)W_WIN / 30, (double)H_WIN * 3 / 5), Vector2D(W_MERCHANT, H_MERCHANT), 1);
	addRenderUpdateLists(merchant);

	//Comprobamos si los NPCs restantes están desbloqueados
	if (gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		NPC* chef;
		chef = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Cooker), Vector2D((double)W_WIN * 3 / 14, H_WIN / 35), Vector2D(W_CHEF, H_CHEF), 2);
		addRenderUpdateLists(chef);
	}

	if (gm_->isThatMissionPass(missions::papelesSiniestros)) {
		//NPC* morty;
		//morty = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Morty), Vector2D(W_WIN / 2, (double)H_WIN * 3 / 4), Vector2D(W_MORTY, H_MORTY), 3);
		//addRenderUpdateLists(morty);
	}

	//Por si se añaden estos NPCs
	//if (gm_->isThatMissionPass(missions::masValePajaroEnMano)) {
	//	NPC* parrot;
	//	parrot = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Parrot), Vector2D(W_WIN / 2, (double)H_WIN * 3 / 4), Vector2D(W_PARROT, H_PARROT), 4);
	//	addRenderUpdateLists(parrot);
	//}

	//if (gm_->isThatMissionPass(missions::misionDelEsqueleto)) {
	//	NPC* skeleton;
	//	skeleton = new NPC(app_, app_->getTextureManager()->getTexture(Resources::SkeletonMusician), Vector2D(W_WIN / 2, H_WIN * 3 / 4), Vector2D(W_SKELETON, H_SKELETON), 5);
	//	addRenderUpdateLists(skeleton);
	//}

	if (gm_->isThatMissionPass(missions::arlongPark)) {
		NPC* cartographer;
		cartographer = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Cartographer), Vector2D((double)W_WIN * 11 / 14, H_WIN / 30), Vector2D(W_CARTOGRAPHER, H_CARTOGRAPHER), 6);
		addRenderUpdateLists(cartographer);
	}
}