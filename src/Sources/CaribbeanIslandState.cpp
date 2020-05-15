#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"
#include "MonkeyCoco.h"
#include "EnemyPirate.h"
#include "Wolf.h"
#include "Skeleton.h"
#include "EndState.h"
#include "WinState.h"

CaribbeanIslandState::~CaribbeanIslandState() { 
	if (currentMap_ != nullptr)delete currentMap_;
	//Reseteo de misiones
	if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		gm_->setStartedMission(missions::gallegaEnProblemas, false);
		gm_->resetMissionCounter(missions::gallegaEnProblemas);
	}
	if (!gm_->isThatMissionPass(missions::papelesSiniestros)) {
		gm_->setStartedMission(missions::papelesSiniestros, false);
		gm_->resetMissionCounter(missions::papelesSiniestros);
	}
	if (!gm_->isThatMissionPass(missions::arlongPark)) {
		gm_->setStartedMission(missions::arlongPark, false);
		gm_->resetMissionCounter(missions::arlongPark);
	}
};

void CaribbeanIslandState::update()
{
	if (enemies_.empty() && gm_->getCurrentZone() == Zone::CaribeanBoss) {
		collisionCtrl_->clearList();
		app_->getAudioManager()->haltMusic();
		app_->getGameStateMachine()->changeState(new ShipState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
}

void CaribbeanIslandState::initState()
{
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(false);

	//Inicializamos el mapa de la zona 1
	initZone1();

	//Inicializamos el hud
	hud_ = new HUD(app_);
	player_->initSkills();
	//Añadimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);
	app_->getAudioManager()->playMusic(Resources::Caribbean, -1);
}

void CaribbeanIslandState::initZone1()
{
	//Se inicia la mision de la cocinera si no se ha completado ya
	/*if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		gm_->setStartedMission(missions::gallegaEnProblemas, true);
	}*/

	/*if (!gm_->isThatMissionPass(missions::papelesSiniestros)) {
		gm_->setStartedMission(missions::papelesSiniestros, true);
	}*/

	if (!gm_->isThatMissionPass(missions::arlongPark)) {
		gm_->setStartedMission(missions::arlongPark, true);
	}

	//Creamos el mapa
	currentMap_ = new TiledMap(app_, this, ZONE1_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS,  Vector2D(app_->getWindowWidth() / 2, 0),  collisionTilesIdZone1, wallTilesIdZone1);
}

void CaribbeanIslandState::initZone2()
{
	currentMap_ = new TiledMap(app_, this, ZONE2_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
}

void CaribbeanIslandState::initZone3()
{
	currentMap_ = new TiledMap(app_, this, ZONE3_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone1);
}

void CaribbeanIslandState::initBossZone()
{
	currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone1);
}

void CaribbeanIslandState::changeZone()
{ 
	delete currentMap_;
	collisionCtrl_->clearList();

	if (gm_->getCurrentZone() == Zone::CaribeanA) {
		deleteExceptHUD(Zone::CaribeanB);
		initZone2();
		addRenderUpdateLists(hud_);
	}
	else if (gm_->getCurrentZone() == Zone::CaribeanB) {
		deleteExceptHUD(Zone::CaribeanC);
		initZone3();
		addRenderUpdateLists(hud_);

	}
	else if (gm_->getCurrentZone() == Zone::CaribeanC) {
		deleteExceptHUD(Zone::CaribeanBoss);
		initBossZone();
		addRenderUpdateLists(hud_);

	}
	hud_->setPlayerInHUD(player_);
	player_->initSkills();
}

