#include "tutorialState.h"
#include "tutorialObject.h"
#include "Chest.h"

void tutorialState::update()
{
	ShipState::update();
	collisionCtrl_->tutorialCollision();
	//Control de tutorial
	switch (gm_->getVenancioPhase())
	{
	case 1:
		//crear botella
		if (!bottleCreated_) {
			createBottle();
		}
		break;
	case 2:
		//crear dummy
		if (!dummyCreated_) {
			gm_->setSkillUnlocked(SkillName::GolpeFuerte);
			createDummy();
		}
		break;
	case 3:
		//crear cofre
		if (!chestCreated_) {
			
			createChest();
		}
		break;
	default:
		break;
	}
}

void tutorialState::initState()
{
	gm_ = GameManager::instance();
	gm_->activeTutorial();
	//Borramos la lista de objetos del barco del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(true);
	tutorialComplete = false;

	collisionMap_ = new TiledMap(app_, this, TILED_MAP, TILE_HEIGHT_TILESET, TILE_WIDTH_TILESET, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::CollisionTile),
		TILESET_FILS, TILESET_COLS, Vector2D(0, 0));

	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::Ship));
	addRenderUpdateLists(background_);

	SDL_Rect destRect; //Rect�ngulo para los objetos

	//Creaci�n del alijo
	destRect.w = W_STASH; destRect.h = H_STASH;
	destRect.x = W_WIN / 2; destRect.y = H_WIN * 2 / 5;
	stash_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::Stash), goStashState);
	addRenderUpdateLists(stash_);
	addObject(stash_);

	//Creaci�n de la trampilla
	destRect.w = W_DOOR; destRect.h = H_DOOR;
	destRect.x = (W_WIN / 2) - W_DOOR * 1.5; destRect.y = H_WIN * 2 / 5 + H_WHEEL / 2;
	door_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ShipDoor), goSaveState);
	addRenderUpdateLists(door_);
	addObject(door_);

	//Creaci�n del timon
	destRect.w = W_WHEEL; destRect.h = H_WHEEL;
	destRect.x = (W_WIN / 2) - W_WHEEL / 2; destRect.y = H_WIN / 7;
	wheel_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::Wheel), goMap);
	addRenderUpdateLists(wheel_);
	addObject(wheel_);

	//Creacion de la salida
	destRect.w = W_EXIT; destRect.h = H_EXIT;
	destRect.x = W_WIN - W_EXIT; destRect.y = H_WIN * 2 / 3;
	
	//exit_a = new Obstacle(app_,destRect, app_->getTextureManager()->getTexture(Resources::ExitShip),Vector2D(destRect.x,doub));

	exit_ = new ShipObject(app_, Vector2D(destRect.x, destRect.y), Vector2D(destRect.w, destRect.h),
		app_->getTextureManager()->getTexture(Resources::ExitShip), nullptr);
	addRenderUpdateLists(exit_);
	addObject(exit_);

	collisionCtrl_->addShipObjects(stash_, door_, wheel_, exit_);
	POST_TUTORIAL_POS = Vector2D((double)(W_WIN / 3), (double)(H_WIN / 7));
	TUTORIAL_POS = Vector2D((double)(destRect.x - W_WIN / 10), (double)(destRect.y - H_WIN / 15));

	createNPCs();	//Método de testeo de los NPCs del barco, faltaría hacer uno definitivo para todos los NPCs desbloqueados

	////Siempre se a�ade el �ltimo para que se renderice por encima de los dem�s objetos
	playerEntry_ = Vector2D((W_WIN - W_PLAYER * 4), ((H_WIN * 3 / 4) - H_PLAYER));
	player_ = new Player(app_, playerEntry_, Vector2D(W_PLAYER, H_PLAYER));
	player_->initSkills();
	player_->setScale(Vector2D(W_PLAYER, H_PLAYER));
	player_->setColliderPos(Vector2D((player_->getScale().getX() / 3), 2 * (player_->getScale().getY() / 4)));
	player_->setColliderScale(Vector2D((player_->getScale().getX() / 3), (player_->getScale().getY() / 4)));

	Camera::instance()->updateCamera(W_WIN / 2, H_WIN / 2);
	addRenderUpdateLists(player_);
	startInstance_ = SDL_GetTicks();
}

void tutorialState::createBottle()
{
	bottleCreated_ = true;
	app_->getWindowHeight() / 7;
	bottlePos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() / 7);
	tutorialObject* bottle = new tutorialObject(app_, bottlePos_, Vector2D(50, 50), app_->getTextureManager()->getTexture(Resources::Bottle));
	collisionCtrl_->setBottle(bottle);
	dynamic_cast<PlayState*>(app_->getCurrState())->addEnemy(bottle);
	collisionCtrl_->addEnemy(bottle);
}

void tutorialState::createDummy()
{
	dummyCreated_ = true;
	app_->getWindowHeight() / 7;
	dummyPos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() * 7 / 10 );
	tutorialObject* dummy = new tutorialObject(app_, dummyPos_, Vector2D(100, 100), app_->getTextureManager()->getTexture(Resources::Dummy));
	collisionCtrl_->setDummy(dummy);
	addEnemy(dummy);
	collisionCtrl_->addEnemy(dummy);
}

void tutorialState::createChest()
{
	chestCreated_ = true;
	Chest* chest = new Chest(app_,dummyPos_,Vector2D(150,150));
	collisionCtrl_->addChest(chest);
	addRenderUpdateLists(chest);
}
