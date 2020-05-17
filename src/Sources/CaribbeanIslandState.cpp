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
};

void CaribbeanIslandState::update()
{
	if (enemies_.empty() && gm_->getCurrentZone() == Zone::CaribeanBoss) {
		collisionCtrl_->clearList();
		//app_->getAudioManager()->haltMusic();
		app_->getGameStateMachine()->changeState(new ShipState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
}

void CaribbeanIslandState::initState()
{
	//Inicializamos la musica
	app_->resetMusicChannels();
	app_->resetSoundsChannels();
	app_->getAudioManager()->playChannel(Resources::Caribbean, -1, Resources::MainMusicChannel);
	app_->getAudioManager()->playChannel(Resources::WavesSound, -1, Resources::AuxMusicChannel1);

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

