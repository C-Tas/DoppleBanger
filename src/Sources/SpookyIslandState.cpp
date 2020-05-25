#include "SpookyIslandState.h"
#include "ShipState.h"
#include "WinState.h"

void backShipSpooky(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}
void SpookyIslandState::initState()
{
	//Inicializamos la musica
	app_->resetMusicChannels();
	app_->resetSoundsChannels();

	//Temporal hasta que esté la música de la isla Spooky
	app_->getAudioManager()->playChannel(Resources::Caribbean, -1, Resources::MainMusicChannel);
	app_->getAudioManager()->playChannel(Resources::WavesSound, -1, Resources::AuxMusicChannel1);

	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(false);

	//Inicializamos el mapa de la zona 1
	//Creamos el mapa
	currentMap_ = new TiledMap(app_, this, ZONE1_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone_, wallTilesIdZone_);

	//Inicializamos el hud
	hud_ = new HUD(app_);
	player_->initSkills();

	//Añadimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);

	//Setteamos que la zona en la que nos encontramos es la SpookyA
	gm_->setCurrentZone(Zone::SpookyA);
	gm_->setCurrIsland(Island::Spooky);
	
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
		//app_->getAudioManager()->haltMusic();
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
	enemies_.clear();

	if (gm_->getCurrentZone() == Zone::SpookyA) {
		deleteExceptHUD(Zone::SpookyBoss);
		currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
			TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone_, wallTilesIdZone_);
		addRenderUpdateLists(hud_);
	}
	hud_->setPlayerInHUD(player_);
	player_->initSkills();
}
