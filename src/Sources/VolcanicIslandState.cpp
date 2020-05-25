#include "VolcanicIslandState.h"
#include "Crab.h"
#include "WinState.h"

void VolcanicIslandState::initState()
{
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
	currentMap_ = new TiledMap(app_, this, BOSSZONE_TILEMAP, TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT, TILE_DRAWING_SIZE, app_->getTextureManager()->getTexture(Resources::TextureId::Tileset1),
		TILESET_FILS, TILESET_COLS, Vector2D(app_->getWindowWidth() / 2, 0), collisionTilesIdZone_, wallTilesIdZone_);

	//Inicializamos el hud
	hud_ = new HUD(app_);
	player_->initSkills();

	//Añadimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);

	//Setteamos que la zona en la que nos encontramos es la SpookyA
	//TO DO: BORRAR LUEGO
	gm_->setCurrentZone(Zone::SpookyA);
	gm_->setCurrIsland(Island::Volcanic);

}

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
	initState();
}

void VolcanicIslandState::update()
{
	if (enemies_.empty() && gm_->getCurrentZone() == Zone::Volcanic) {
		collisionCtrl_->clearList();
		//app_->getAudioManager()->haltMusic();
		app_->getGameStateMachine()->changeState(new WinState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
}
