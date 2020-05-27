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
	if (currentMap_ != nullptr) delete currentMap_;
	//Reseteo de misiones
	if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		gm_->setStartedMission(missions::gallegaEnProblemas, false);
		gm_->resetMissionCounter(missions::gallegaEnProblemas);
	}
};

void CaribbeanIslandState::update()
{
	if (enemies_.empty() && gm_->getCurrentZone() == Zone::CaribeanBoss) {
		collisionCtrl_->clearList();
		gm_->setUnlockedIslands(Island::Spooky);
		app_->getGameStateMachine()->changeState(new ShipState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
}

void CaribbeanIslandState::initState()
{
	//Resteo de la isla
	gm_->setCurrentZone(Zone::CaribeanA);
	gm_->setCurrIsland(Island::Caribbean);

	//Inicializamos la musica
	app_->resetMusicChannels();
	app_->resetSoundsChannels();
	
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
}

void CaribbeanIslandState::initZone1()
{
	//Se inicia la música
	app_->getAudioManager()->playChannel(Resources::Isle1Zone1, -1, Resources::MainMusicChannel);

	//Se inicia la mision de la cocinera si no se ha completado ya
	if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		gm_->setStartedMission(missions::gallegaEnProblemas, true);
	}

	//Creamos el mapa
	currentMap_ = new TiledMap(app_, this, ZONE1_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS,  Vector2D(app_->getWindowWidth() / 2, 0),  collisionTilesIdZone1, wallTilesIdZone1);
}

void CaribbeanIslandState::initZone2()
{
	//Se inicia la música
	app_->getAudioManager()->playChannel(Resources::Isle1Zone2, -1, Resources::MainMusicChannel);

	currentMap_ = new TiledMap(app_, this, ZONE2_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
}

void CaribbeanIslandState::initZone3()
{
	GameManager* gm_ = GameManager::instance();
	if (!gm_->isThatMissionPass(missions::masValePajaroEnMano)) {
		gm_->setMissionFinished(missions::masValePajaroEnMano, true);
	}
	
	//Se inicia la música
	app_->getAudioManager()->playChannel(Resources::Isle1Zone3, -1, Resources::MainMusicChannel);

	currentMap_ = new TiledMap(app_, this, ZONE3_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
}

void CaribbeanIslandState::initBossZone()
{
	currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
}

void CaribbeanIslandState::changeZone()
{ 
	delete currentMap_;
	collisionCtrl_->clearList();

	enemies_.clear();
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