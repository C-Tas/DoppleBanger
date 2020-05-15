#include "SpookyIslandState.h"
#include "ShipState.h"
#include "WinState.h"

void backShipSpooky(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}
void SpookyIslandState::initState()
{
	gm_->setOnShip(false);
	//background_ = app_->getTextureManager()->getTexture(Resources::Spooky);
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();

	//Creamos el mapa
	currentMap_ = new TiledMap(app_,this, ZONE1_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS,  Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone1);

	addRenderUpdateLists(hud_);
}

SpookyIslandState::SpookyIslandState(Application* app) : PlayState(app)
{
	initState();
}

SpookyIslandState::~SpookyIslandState()
{
	delete currentMap_;
}

void SpookyIslandState::update()
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

void SpookyIslandState::changeZone()
{
	delete currentMap_;
	collisionCtrl_->clearList();

	if (gm_->getCurrentZone() == Zone::SpookyA) {
		deleteExceptHUD(Zone::SpookyB);
		currentMap_ = new TiledMap(app_, this, ZONE2_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
			TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
		addRenderUpdateLists(hud_);
	}
	else if (gm_->getCurrentZone() == Zone::SpookyB) {
		deleteExceptHUD(Zone::SpookyC);
		currentMap_ = new TiledMap(app_, this, ZONE3_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
			TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
		addRenderUpdateLists(hud_);

	}
	else if (gm_->getCurrentZone() == Zone::SpookyC) {
		deleteExceptHUD(Zone::SpookyBoss);
		currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
			TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone1, wallTilesIdZone2);
		addRenderUpdateLists(hud_);
	}
	hud_->setPlayerInHUD(player_);
	player_->initSkills();
}
