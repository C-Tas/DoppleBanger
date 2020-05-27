#include "SpookyIslandState.h"
#include "ShipState.h"
#include "WinState.h"

void backShipSpooky(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}
void SpookyIslandState::initState()
{
	//Resetamos los sonidos
	app_->resetMusicChannels();
	app_->resetSoundsChannels();


	gm_->setOnShip(false);
	//background_ = app_->getTextureManager()->getTexture(Resources::Spooky);
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(false);

	//Se inicia la mision del músico si no se ha completado ya
	if (!gm_->isThatMissionPass(missions::laboon)) {
		gm_->setStartedMission(missions::laboon, true);
	}

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
	
}

SpookyIslandState::SpookyIslandState(Application* app) : PlayState(app)
{
	initState();
}

SpookyIslandState::~SpookyIslandState()
{
	delete currentMap_;

	//Reseteo de misiones
	if (!gm_->isThatMissionPass(missions::laboon)) {
		gm_->setStartedMission(missions::laboon, false);
		gm_->resetMissionCounter(missions::laboon);
	}
}

void SpookyIslandState::update()
{
	if (gm_->endDemo()) {
		collisionCtrl_->clearList();
		gm_->setUnlockedIslands(Island::Volcanic);
		app_->getGameStateMachine()->changeState(new WinState(app_));
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

		//Se inicia la música
		app_->getAudioManager()->playChannel(Resources::Isle2Zone1, -1, Resources::MainMusicChannel);
		currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
			TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone_, wallTilesIdZone_);
		addRenderUpdateLists(hud_);
	}
	hud_->setPlayerInHUD(player_);
	player_->initSkills();
}
